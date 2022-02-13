#pragma once

#include <functional>
#include <memory>
#include <vector>
#include <type_traits>
#include <Windows.h>
#include <spdlog/spdlog.h>
#include <Helper/Singleton.hpp>
#include <Helper/Pointer.hpp>

#include "CheatException.hpp"

namespace GCLAX2
{
    template <typename ClassType>
        requires requires (ClassType)
    {
        !std::is_same_v<ClassType, unsigned char*>;
        std::is_scalar_v<ClassType>;
        std::is_nothrow_convertible_v<ClassType, unsigned char*>;
    }
    class VTableManager : Singleton<VTableManager<ClassType>>
    {
        intptr_t* vtable_ = nullptr;
        std::vector<intptr_t> old_vtable_ {};
        size_t vtable_entry_count_ = 0;
        bool is_vtable_existed_ = false;

    public:
        virtual ~VTableManager<ClassType>() noexcept
        {
            this->is_vtable_existed_ = false;
            this->vtable_ = nullptr;
            this->vtable_entry_count_ = 0;
            old_vtable_.clear();
        }

        VTableManager<ClassType>(const VTableManager<ClassType>&) = delete;

        VTableManager<ClassType>(VTableManager<ClassType>&&) = delete;

        VTableManager<ClassType>& operator=(const VTableManager<ClassType>&) = delete;

        VTableManager<ClassType>& operator=(VTableManager<ClassType>&&) = delete;

        const bool isVTableExist() const noexcept
        {
            return this->is_vtable_existed_;
        }

        intptr_t* getVTableAddress() const noexcept
        {
            return this->vtable_;
        }

        void restore() noexcept
        {
            for (size_t i = 0; i < this->vtable_entry_count_; i++)
                this->unhook(i);
        }

        template<typename FuncProtoType>
        void hook(const size_t tableIndex, const FuncProtoType hookFunc) noexcept
        {
            try
            {
                if (this->is_vtable_existed_)
                {
                    if (tableIndex < this->vtable_entry_count_)
                    {
                        this->vtable_[tableIndex] = reinterpret_cast<intptr_t>(hookFunc);
                    }
                    else
                    {
                        throw IndexOutOfBoundVirtualTableError{};
                    }
                }
                else
                {
                    throw InvalidVirtualTableError{};
                }
            }
            catch (const InvalidVirtualTableError&)
            {
                spdlog::error("virtual table cannot be found");
            }
            catch (const IndexOutOfBoundVirtualTableError&)
            {
                spdlog::error("Access out of bound index of virtual table entry");
                if (this->vtable_entry_count_ == 0)
                {
                    spdlog::warn("virtual table has 0 entry");
                }
            }
            catch (...)
            {
                spdlog::critical("Unknown error is caught");
                exit(EXIT_FAILURE);
            }
        }

        void unhook(const size_t tableIndex) noexcept
        {
            try
            {
                if (this->is_vtable_existed_)
                {
                    if (tableIndex < this->vtable_entry_count_)
                    {
                        this->vtable_[tableIndex] = reinterpret_cast<intptr_t>(this->old_vtable_.at(tableIndex));
                    }
                    else
                    {
                        throw IndexOutOfBoundVirtualTableError{};
                    }
                }
            }
            catch (const InvalidVirtualTableError&)
            {
                spdlog::error("Access out of bound index of virtual table entry");
                if (this->vtable_entry_count_ == 0)
                {
                    spdlog::warn("virtual table has 0 entry");
                }
            }
            catch (...)
            {
                spdlog::critical("Unknown error is caught");
                exit(EXIT_FAILURE);
            }
        }
        
        template<typename MemberFuncProto>
        const auto getOriginalMemberFunctionPointer(ClassType* obj, size_t index)
        {
            MemberFuncProto mfp = *(MemberFuncProto*)&this->old_vtable_.at(index);
            return mfp;
        }

    private:

        explicit VTableManager<ClassType>() noexcept = default;

        explicit VTableManager<ClassType>(ClassType * classBase) noexcept : VTableManager<ClassType>{ reinterpret_cast<unsigned char*>(classBase) } {}

        explicit VTableManager<ClassType>(unsigned char* classBase) noexcept
        {
            Pointer ptr{ classBase };
            this->vtable_ = ptr.dereference().to<intptr_t*>();

            MEMORY_BASIC_INFORMATION memInfo{ 0 };
            try
            {
                if (VirtualQuery(this->vtable_, &memInfo, sizeof(memInfo)) != 0)
                {
                    if (this->isVTableRegion(memInfo))
                    {
                        size_t entryCount = 0;
                        const Pointer vtable{ this->vtable_ };
                        while (true)
                        {
                            Pointer entry = vtable.offset(entryCount * 8).dereference();
                            if (VirtualQuery(entry.to<unsigned char*>(), &memInfo, sizeof(memInfo)) != 0)
                            {
                                if (this->isValidVTableEntry(memInfo))
                                {
                                    spdlog::debug("Entry 0x{:X} is found", entry.to<uint64_t>());
                                    entryCount++;
                                    this->old_vtable_.emplace_back(entry.to<uint64_t>());
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                throw VirtualQueryError{};
                            }
                        }

                        spdlog::debug("Stop scanning virtual table. Total entry size : {}", entryCount);
                        this->vtable_entry_count_ = entryCount;
                        this->is_vtable_existed_ = true;
                    }
                    else
                    {
                        throw InvalidVirtualTableError{};
                    }
                }
                else
                {
                    throw VirtualQueryError{};
                }
            }
            catch (const InvalidVirtualTableError&)
            {
                const uint64_t address = reinterpret_cast<uint64_t>(this->vtable_);
                spdlog::warn("Address 0x{:X} is not a valid virtual table", address);
                this->vtable_ = nullptr;
                this->is_vtable_existed_ = false;
            }
            catch (const VirtualQueryError&)
            {
                spdlog::error("VirtualQuery fails");
                this->vtable_ = nullptr;
                this->is_vtable_existed_ = false;
            }
            catch (...)
            {
                spdlog::error("Catch unknown error !");
                this->vtable_ = nullptr;
                this->is_vtable_existed_ = false;
            }
        }

        const bool isVTableRegion(MEMORY_BASIC_INFORMATION& memInfo) const noexcept
        {
            return (memInfo.State == MEM_COMMIT) &&
                (memInfo.Protect & (PAGE_READONLY | PAGE_READWRITE)) &&
                (memInfo.Protect & (PAGE_GUARD | PAGE_NOACCESS)) == 0;
        }

        const bool isValidVTableEntry(MEMORY_BASIC_INFORMATION& memInfo) const noexcept
        {
            return (memInfo.State == MEM_COMMIT) &&
                (memInfo.Protect & (PAGE_EXECUTE_READ)) &&
                (memInfo.Protect & (PAGE_GUARD | PAGE_NOACCESS)) == 0;
        }

        friend class Singleton<VTableManager<ClassType>>;
    };
}