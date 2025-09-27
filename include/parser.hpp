/**
 * @file parser.hpp
 * @brief Header file for the parser of the linker.
 *
 * This module handles Phase 1 of the static linker:
 * - Reads a single object file
 * - Extracts symbols (functions, globals, components)
 * - Stores them in memory for later symbol resolution and memory layout
 *
 * Phase 1 is limited to a single object file; multi-file linking is handled later.
 */

/// @note Phase 1 supports only a single object file. Multi-file support comes in later phases.

#pragma once
#include <string>
#include <vector>

/**
 *@enum SymbolType
 *@brief Represents the type of the symbol
 *
 *There are currently 3 types of symbols
 *-GLOBAL: Global variable
 *-FUNCTION: Function
 *-COMPONENT: component
 **/
enum class SymbolType
{
    GLOBAL,
    FUNCTION,
    COMPONENT,
};

/**
 * @struct Symbol
 * @brief Represents a named entity in an object file.
 *
 * Each Symbol has:
 * - name: Identifier used for symbol resolution
 * - type: Function, global variable, or component
 * - size: Memory footprint
 * - offset: Assigned memory location (computed in later linker phases)
 */
struct Symbol
{
    std::string name; ///< Name of the symbol
    SymbolType type;  ///< Type of the symbol
    size_t size;      ///< Size in bytes
    size_t offset;    ///< Memory offset after layout
};

/**
 * @class Parser
 * @brief Parses object files and builds an in-memory symbol table.
 *
 * Responsibilities:
 * 1. Open a compiler-generated object file
 * 2. Parse header and symbol section
 * 3. Populate a vector of Symbol structs
 * 4. Perform basic sanity checks
 *
 * The output is used by the linker to perform memory layout
 * and eventually write the final executable.
 */
class Parser
{
public:
    Parser();
    /**
     * @brief Parses a single object file and populates the symbol table.
     *
     * @param filename Path to the compiler-generated object file.
     *
     * Workflow:
     * 1. Opens the file in binary mode
     * 2. Reads header info and number of symbols
     * 3. Reads each symbol and stores in internal vector
     * 4. Prints debug info for Phase 1 testing
     */
    void parseObj(const std::string &filename);

    /**
     * @brief Generates a vector containing the symbols
     */
    std::vector<Symbol> generateSymbolsVector();

private:
    std::vector<Symbol> symbols; // The symbols
};