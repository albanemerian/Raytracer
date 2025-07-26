# Errors

The exception handling system in the raytracer project is designed to provide a structured and extensible way to manage errors. It uses a hierarchy of exception classes to categorize and handle different types of errors effectively.

## Architecture Overview

The exception system is composed of the following files:

1. **`IException.hpp`** (Interface) [Go to Page 48](../../Doc.pdf#page=50)
2. **`AException.hpp`** (Abstract Base Class) [Go to Page 11](../../Doc.pdf#page=12)
3. **`CommandException.hpp`** (Specific Exception)
4. **`FileException.hpp`** (Specific Exception)

### 1. `IException.hpp`

- **Purpose**: Defines the interface for all exceptions in the system.
- **Key Features**:
  - Inherits from `std::exception`.
  - Declares pure virtual methods:
    - `what() const noexcept`: Returns a description of the error.
    - `getType() const noexcept`: Returns the type of the exception.
    - `getMessage() const noexcept`: Returns the error message.
    - `getFormattedMessage() const noexcept`: Returns a formatted string combining the type and message.

This interface ensures that all exceptions in the system follow a consistent structure.

---

### 2. `AException.hpp`

- **Purpose**: Provides a base implementation for exceptions, inheriting from `IException`.
- **Key Features**:
  - Implements the `what()`, `getType()`, `getMessage()`, and `getFormattedMessage()` methods.
  - Stores the exception type (`_type`) and message (`_message`) as private members.
  - Formats the error message as `[Type] Message`.

This class serves as a reusable base for specific exceptions, reducing code duplication.

---

### 3. `CommandException.hpp`

- **Purpose**: Represents errors related to command handling.
- **Key Features**:
  - Inherits from `AException`.
  - Constructor initializes the exception with a type of `"CommandError"` and a custom message.

This class is used to handle errors specific to command-related operations.

---

### 4. `FileException.hpp`

- **Purpose**: Represents errors related to file operations.
- **Key Features**:
  - Inherits from `AException`.
  - Constructor initializes the exception with a type of `"FileError"` and a custom message.

This class is used to handle errors specific to file-related operations.

---

## Workflow

1. **Throwing Exceptions**:
   - When an error occurs, the appropriate exception class is instantiated and thrown.
   - Example:
     ```cpp
     throw CommandException("Invalid command syntax");
     ```

2. **Catching Exceptions**:
   - Exceptions are caught using `try-catch` blocks.
   - Example:
     ```cpp
     try {
         // Code that may throw an exception
     } catch (const IException& e) {
         std::cerr << e.what() << std::endl;
     }
     ```

3. **Error Reporting**:
   - The `what()` method provides a formatted error message for logging or debugging.
   - Example Output:
     ```
     [CommandError] Invalid command syntax
     ```

---

## Benefits of the Architecture

- **Modularity**: Each exception type is encapsulated in its own class, making the system easy to extend.
- **Reusability**: The `AException` base class provides common functionality, reducing code duplication.
- **Consistency**: The `IException` interface ensures that all exceptions follow a standard structure.
- **Readability**: Formatted error messages make debugging easier.

This architecture provides a robust and scalable way to handle errors in the raytracer project.
