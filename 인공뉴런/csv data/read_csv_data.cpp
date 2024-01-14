#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// CSV 파일을 읽어서 데이터를 처리하는 함수
void processCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return;
    }

    std::string line;
    std::vector<std::vector<std::string>> data;

    // CSV 파일을 한 줄씩 읽어서 데이터를 저장
    while (std::getline(file, line)) {
        std::vector<std::string> row;
        size_t start = 0;
        size_t end = line.find(',');

        // 쉼표로 구분된 각 열의 데이터를 분리하여 저장
        while (end != std::string::npos) {
            std::string value = line.substr(start, end - start);
            row.push_back(value);
            start = end + 1;
            end = line.find(',', start);
        }

        // 마지막 열의 데이터를 저장
        std::string value = line.substr(start, end);
        row.push_back(value);

        // 데이터를 2차원 벡터에 저장
        data.push_back(row);
    }

    // 데이터 처리 예시: 각 행의 데이터 출력
    for (const auto& row : data) {
        for (const auto& value : row) {
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }

    file.close();
}

int main() {
    std::string filename = "data.csv";
    processCSV(filename);

    return 0;
}
