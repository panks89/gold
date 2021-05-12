#pragma once

#include <atomic>
#include <mutex>

namespace local {
    
    template<typename T>
    class ControlBlockBase
    {
        std::atomic<size_t> mReferenceCount = 0u;
    public:
        virtual ~ControlBlockBase() = default;
        
        virtual T* get() = 0;
        
        void addReference() { ++mReferenceCount; }
        
        void removeReference() { --mReferenceCount; }
        
        size_t countReferences() { return mReferenceCount; }
        
        std::mutex mMutex;
    };

    template <typename T>
    class IntegratedControlBlock : public ControlBlockBase<T> {
        T mObject;
    public:
        
        template <typename ...U>
        IntegratedControlBlock(U&& ...args) : mObject{ std::forward<U>(args)... } {
            ControlBlockBase<T>::addReference();
        }

        T* get() override { return &mObject;  }
    };

    struct DefaultDeleter {
        template <typename T>
        void operator()(T* ptr) {
            delete ptr;
        }
    };

    template <typename T, typename Deleter>
    class ControlBlock : public ControlBlockBase<T> {
        T* mPointer;
        Deleter mDeleter;
    public:

        ControlBlock(T* pointer, Deleter deleter) : mPointer{ pointer }, mDeleter{ deleter } {
            ControlBlockBase<T>::addReference();
        }

        T* get() override { return mPointer; }

        ~ControlBlock() {
            if (mPointer) {
                mDeleter(mPointer);
            }
        }
    };

    
    
    template <typename T, typename Deleter = DefaultDeleter>
    class shared_ptr {
        ControlBlockBase<T>* mBlockPointer;
    public:
        shared_ptr(T* pointer, Deleter deleter = DefaultDeleter{}) : mBlockPointer{ new ControlBlock<T, Deleter>(pointer, deleter) } {
        
        }

        template <typename ...U>
        shared_ptr(U&& ...args) : mBlockPointer{ new IntegratedControlBlock<T>(std::forward<U>(args)...) } {
        
        }

        // copy constructor
        shared_ptr(const shared_ptr& sptr) : mBlockPointer{ sptr.mBlockPointer } {
            mBlockPointer->addReference();
        }

        // move constructor
        shared_ptr(shared_ptr&& sptr) noexcept : mBlockPointer{ sptr.mBlockPointer } {
            sptr.mBlockPointer = nullptr;
        }

        // assignment constructor using copy and swap idiom
        shared_ptr& operator=(shared_ptr sptr) {
            std::swap(mBlockPointer, sptr.mBlockPointer);
            return *this;
        }

        // destructor
        ~shared_ptr() {
            // return if moved from state object
            if (!mBlockPointer) { return; }
            mBlockPointer->mMutex.lock();
            mBlockPointer->removeReference();
            if (mBlockPointer->countReferences() == 0) {
                mBlockPointer->mMutex.unlock();
                delete mBlockPointer;
            }
            else {
                mBlockPointer->mMutex.unlock();
            }
        }

        T& operator*() const {
            return *(mBlockPointer->get());
        }

        const size_t use_count() const {
            return mBlockPointer->countReferences();
        }
    };

    template <typename T, typename ...U>
    shared_ptr<T> make_shared(U&& ...args) {
        return shared_ptr{ std::forward<U>(args)... };
    }
}