#include <iostream>
#include <vector>

using namespace std;

class MyException {
public:
	string message;
	int line;

	MyException(string message, int line) {
		this->message = message;
		this->line = line;
	}
};

class DISC {
	double currentSize = 0;
	int writeTime = 1;

private:
	class File {
	private:
		double fileSize;

	public:
		string fileName;
		string content;
		int hour;

		File(string fileName, int hour, string content = "") {
			this->fileName = fileName;
			this->content = content;
			this->hour = hour;
			fileSize = content.length() * 2;
		};

		double GetFileSize() {
			return fileSize;
		}

		void SetFileSize(double size) {
			fileSize = size;
		}
	};

	vector<File> Files;

public:
	const static double maxSize;

	DISC(int writeTime) {
		this->writeTime = writeTime;
	}

	File& getFile(string fileName) {
		for (auto i : Files) {
			if (i.fileName == fileName) {
				return i;
			}
		}

		MyException notFound("Bu adda file yoxdur.", 62);
		throw notFound;
	}

	bool isExistsFile(string fileName) {
		bool check = false;

		for (auto i : Files) {
			if (i.fileName == fileName) {
				check = true;
			}
		}

		return check;
	}

	void createFile(string fileName, int hour, string content = "") {
		for (auto i : Files) {
			if (i.fileName == fileName) {
				MyException eyniaddafile("Bu adda file var.", 85);
				return;
			}
		}

		if (((content.length() * 2) + currentSize) > maxSize) {
			MyException sizeProblem("Kiyafet qeder yer yoxdur.", 93);
			return;
		}

		File newfile(fileName, hour, content);
		int seconds = newfile.GetFileSize() / writeTime;

		while (seconds >= 0) {
			cout << "Zehmet olmasa " << seconds << " gozleyin.";
			system("cls");
		}

		Files.push_back(newfile);
		currentSize += content.length() * 2;
	}

	void setFileContent(string fileName, string content = "") {
		for (auto i : Files) {
			if (i.fileName == fileName) {
				if ((((content.length() * 2) + currentSize) - i.content.length()) > maxSize) {
					MyException sizeProblem("Kiyafet qeder yer yoxdur.", 93);
					return;
				}

				int seconds = (content.length() * 2) / writeTime;

				while (seconds >= 0) {
					cout << "Zehmet olmasa " << seconds << " gozleyin.";
					system("cls");
				}

				currentSize -= content.length() * 2;
				i.content = content;
				i.SetFileSize(content.length() * 2);
				currentSize += content.length() * 2;
				return;
			}
		}

		MyException fileyoxdu("Bu adda file yoxdur.", 125);
		throw fileyoxdu;
	}

	void deleteFileContent(string fileName) {
		bool check = false;
		int id = 0;

		for (auto i : Files) {
			if (i.fileName == fileName) {
				check = true;
				currentSize -= i.content.length() * 2;
			}

			id++;
		}

		if (check) {
			Files.erase(Files.begin() + (id - 1));
		}

		else {
			MyException fileyoxdu("Bu adda file yoxdur.", 148);
			throw fileyoxdu;
		}
	}

	void showAllFiles() {
		int index = 0;

		cout << "Fayllar :" << endl;
		for (auto file : Files) {
			cout << index << ". Fayl:\n" << "Ad: " << file.fileName << "Fayl Yaranma Zamani: " << file.hour << "Fayl Olcusu: " << file.GetFileSize();
		}

	}
};

class HDD : DISC {
public:
	const static double maxSize;

	HDD(int writeTime) : DISC(writeTime) {}
};

class SSD : DISC {
public:
	const static double maxSizeSSD;
	SSD(int writeTime) : DISC(writeTime) {}
};

const double HDD::maxSize = 100;
const double SSD::maxSizeSSD = 100;

class OperationSystem {
	OperationSystem() {}

public:
	static void controlPC();
};

void Start() {
	OperationSystem::controlPC();
	
	try {
		// kodlarr
	}

	catch (MyException exception) {
		cout << "Error : " << exception.message << endl;
	}
}

void main() {
	Start();
}