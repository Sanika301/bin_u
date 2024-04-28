#include <iostream>
#include <fstream>
#include <string>

void cat(const std::string &filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    std::cerr << "Error: Couldn't open file " << filename << std::endl;
    return;
  }

  std::string line;
  while (std::getline(file, line))
  {
    std::cout << line << std::endl;
  }

  file.close();
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  cat(argv[1]);
  return 0;
}

// #include <iostream>
// #include <filesystem>

// namespace fs = std::filesystem;

// void ls(const std::string& path) {
//     for (const auto& entry : fs::directory_iterator(path)) {
//         std::cout << entry.path().filename() << std::endl;
//     }
// }

// int main(int argc, char *argv[]) {
//     std::string path = ".";
//     if (argc == 2) {
//         path = argv[1];
//     }

//     ls(path);
//     return 0;
// }

// #include <iostream>
// #include <fstream>

// void cp(const std::string& src, const std::string& dest) {
//     std::ifstream source(src, std::ios::binary);
//     std::ofstream destination(dest, std::ios::binary);
//     destination << source.rdbuf();
// }

// int main(int argc, char *argv[]) {
//     if (argc != 3) {
//         std::cerr << "Usage: " << argv[0] << " <source> <destination>" << std::endl;
//         return 1;
//     }

//     cp(argv[1], argv[2]);
//     return 0;
// }

// #include <iostream>
// #include <filesystem>

// namespace fs = std::filesystem;

// void mv(const std::string& src, const std::string& dest) {
//     try {
//         fs::rename(src, dest);
//     } catch (const std::exception& e) {
//         std::cerr << "Error: " << e.what() << std::endl;
//     }
// }

// int main(int argc, char *argv[]) {
//     if (argc != 3) {
//         std::cerr << "Usage: " << argv[0] << " <source> <destination>" << std::endl;
//         return 1;
//     }

//     mv(argv[1], argv[2]);
//     return 0;
// }

// #include <iostream>
// #include <fstream>
// #include <string>

// void head(const std::string& filename, int lines) {
//     std::ifstream file(filename);
//     if (!file.is_open()) {
//         std::cerr << "Error: Couldn't open file " << filename << std::endl;
//         return;
//     }

//     std::string line;
//     int count = 0;
//     while (std::getline(file, line) && count < lines) {
//         std::cout << line << std::endl;
//         count++;
//     }

//     file.close();
// }

// int main(int argc, char *argv[]) {
//     if (argc != 3) {
//         std::cerr << "Usage: " << argv[0] << " <filename> <lines>" << std::endl;
//         return 1;
//     }

//     int lines = std::stoi(argv[2]);
//     head(argv[1], lines);
//     return 0;
// }
