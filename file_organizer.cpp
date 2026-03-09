#include <iostream>
#include <filesystem>
#include <set>
#include <algorithm>
#include <cctype>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char* argv[]) {

    if(argc < 2){
        cout << "Usage: organizer <C:\\Users\\DELL\\OneDrive\\C.vs\\TestFolder>\n";
        return 1;
    }

    string folderPath = argv[1];

    int images = 0, documents = 0, music = 0, others = 0;

    set<string> seen;

    for(auto &file : fs::directory_iterator(folderPath)){

        // Skip directories
        if(fs::is_directory(file))
            continue;

        string name = file.path().filename().string();

        // Duplicate filename detection
        if(seen.count(name)){
            cout << "Duplicate detected: " << name << endl;
        }
        else{
            seen.insert(name);
        }

        // Get file extension
        string ext = file.path().extension().string();

        // Convert extension to lowercase
        transform(ext.begin(), ext.end(), ext.begin(),
                  [](unsigned char c){ return tolower(c); });

        string category;

        if(ext == ".jpg" || ext == ".png"){
            category = "Images";
            images++;
        }
        else if(ext == ".pdf"){
            category = "Documents";
            documents++;
        }
        else if(ext == ".mp3"){
            category = "Music";
            music++;
        }
        else{
            category = "Others";
            others++;
        }

        // Create folder if it doesn't exist
        fs::create_directories(folderPath + "/" + category);

        // Move file
        fs::rename(file.path(),
                   folderPath + "/" + category + "/" + name);

        cout << "Moved " << name << " to " << category << endl;
    }

    cout << "\nSummary\n";
    cout << "Images: " << images << endl;
    cout << "Documents: " << documents << endl;
    cout << "Music: " << music << endl;
    cout << "Others: " << others << endl;

    return 0;
}