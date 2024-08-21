/**
 * @file memory.hxx
 * @brief Defines the Memory class for managing dynamic memory allocation in the Zylo programming language.
 *
 * This file contains the declaration of the `Memory` class, which is responsible for handling
 * dynamic memory allocation, deallocation, and tracking of allocated objects within the Zylo
 * programming language runtime. The `Memory` class provides methods to create new objects,
 * track their pointers, and safely release memory when it is no longer needed, ensuring efficient
 * memory management throughout the execution of Zylo programs.
 */

#ifndef ZYLO_MEMORY_HXX // ZYLO_MEMORY_HXX
#define ZYLO_MEMORY_HXX

#include <vector>

namespace zylo
{
    /**
     * @class Memory
     * @brief A class responsible for managing memory allocation and deallocation in the programming language.
     *
     * The Memory class provides methods for allocating, deallocating, and reallocating memory blocks,
     * facilitating dynamic memory management within the language. It is designed to efficiently handle
     * memory resources, ensuring reuse and minimizing fragmentation.
     */
    class Memory
    {
    public:
        /**
         * @brief Constructs a Memory object.
         *
         * Initializes the Memory class, setting up the internal structures required for memory management.
         * This constructor prepares the memory pool and any necessary initial configurations before memory
         * can be allocated or deallocated.
         */
        Memory();

        /**
         * @brief Destructs a Memory object.
         *
         * Cleans up the Memory class, releasing any resources allocated during the lifetime of the object.
         * This destructor ensures that all memory blocks are deallocated and that the memory pool is released.
         */
        ~Memory();

        /**
         * @brief Creates a new instance of a specified type and manages its memory.
         *
         * This template method dynamically allocates memory for an object of the specified type `Type`,
         * stores the pointer in an internal list for later management, and returns the pointer to the caller.
         * This is useful for managing dynamically allocated objects and ensuring they can be tracked
         * and deallocated properly.
         *
         * @tparam Type The type of the object to be created. This can be any class or struct type.
         * @return Type* A pointer to the newly created object of type `Type`.
         *
         * @note The caller is responsible for ensuring that the object is properly managed and deallocated,
         * either manually or through a management system provided by the class (e.g., a destructor that
         * cleans up the stored pointers).
         */
        template <typename Type>
        Type *create()
        {
            Type *pointer = new Type();
            pointers.push_back(pointer);
            return pointer;
        }

        /**
         * @brief Clears all managed pointers and deallocates their associated memory.
         *
         * This method iterates through all the pointers stored in the internal list, deletes each one to
         * deallocate its memory, and then clears the list of pointers. After calling this method, all
         * dynamically allocated objects managed by this class will be destroyed, and their memory
         * will be released.
         *
         * @note After calling `clear()`, all pointers previously managed by this class become invalid.
         * Attempting to use them will result in undefined behavior.
         *
         * @warning Ensure that no other part of your code is holding onto the pointers managed by this
         * class before calling `clear()`, as this will lead to dangling pointers.
         */
        void clear();

        /**
         * @brief Retrieves the current number of managed pointers.
         *
         * This method returns the number of pointers currently stored and managed by this class.
         * It is useful for checking how many objects are being managed, which can help in memory
         * management and debugging.
         *
         * @return int The number of pointers currently managed by the class.
         *
         * @note This method is marked as `const`, meaning it does not modify any members of the class.
         */
        int pointers_count() const;

    private:
        /**
         * @brief A collection of pointers managed by the class.
         *
         * This private member stores pointers to dynamically allocated memory blocks.
         * The class is responsible for managing these pointers, including their allocation,
         * deallocation, and ensuring no memory leaks occur. The `pointers` vector holds
         * raw pointers (`void*`) which can point to any type of object.
         *
         * @note As this member is private, direct access to it is restricted. Management
         * of these pointers should be done through the public methods provided by the class,
         * such as `create()`, `clear()`, and any other memory management methods.
         *
         * @warning Manual manipulation of this vector outside the class is not recommended
         * and could lead to memory management issues, such as leaks or undefined behavior.
         */
        std::vector<void *> pointers;
    };

    /**
     * @brief A global pointer to a Memory instance used for managing dynamic memory operations.
     *
     * This `extern` declaration allows `globalMemory` to be accessible across multiple translation
     * units. It points to a `Memory` object that is responsible for allocating, deallocating,
     * and managing memory throughout the program.
     *
     * @note The actual definition of `globalMemory` must be provided in one of the source files
     * (typically a `.cpp` file). This declaration allows other parts of the program to use
     * the same `Memory` instance without creating additional copies.
     *
     * @warning Ensure that `globalMemory` is properly initialized before any operations are
     * performed on it. Accessing an uninitialized or null `globalMemory` pointer will result
     * in undefined behavior.
     */
    extern Memory *global_memory;

} // namespace zylo

#endif