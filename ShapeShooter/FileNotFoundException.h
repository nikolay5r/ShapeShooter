#pragma once
#include <exception>
#include <string>

class FileNotFoundException : public std::exception
{
public:
    /** Constructor (C strings).
     *  @param message C-style string error message.
     *                 The string contents are copied upon construction.
     *                 Hence, responsibility for deleting the char* lies
     *                 with the caller.
     */
    explicit FileNotFoundException(const char* message);

    /** Constructor (C++ STL strings).
     *  @param message The error message.
     */
    explicit FileNotFoundException(const std::string& message);

    /** Destructor.
     * Virtual to allow for subclassing.
     */
    virtual ~FileNotFoundException() noexcept;

    /** Returns a pointer to the (constant) error description.
     *  @return A pointer to a const char*. The underlying memory
     *          is in posession of the Exception object. Callers must
     *          not attempt to free the memory.
     */
    virtual const char* what() const noexcept;

protected:
    /** Error message.
     */
    std::string message;
};

