// removeEmptySubDirs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// Function to remove empty directories recursively
void removeEmptyDirs(fs::path path)
{
    // Check if the given path is a directory
    if (!fs::is_directory(path)) { return; } // If it's not, return without doing anything

    bool empty = true; // Assume the directory is empty unless we find files or subdirectories

    try
    {
        // Loop over each entry (file or subdirectory) in the directory
        for (auto& entry : fs::directory_iterator(path))
        {
            try
            {
                removeEmptyDirs(entry); // Recursively remove empty directories in each subdirectory
                empty = false; // If we found an entry, the directory is not empty
            }
            catch (const std::exception& e) { std::cerr << "Error removing directory: " << e.what() << std::endl; }
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
        return;
    }

    // If the directory is empty, delete it
    if (empty)
    {
        try
        {
            std::cout << "Removing empty directory: " << path << std::endl;
            fs::remove(path);
        }
        catch (const std::exception& e) { std::cerr << "Error removing directory: " << e.what() << std::endl; }
    }
}

int main() {
    
    fs::path c_drive("C:\\"); // Create a path object for the C: drive   
    removeEmptyDirs(c_drive); // Call remove_empty_dirs on the root directory of the C: drive
    std::cout << "Done." << std::endl; // Print a message when finished
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
