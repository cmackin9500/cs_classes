#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

struct Pixel {
	unsigned int red;
	unsigned int green;
	unsigned int blue;
};
// a structure named Pixel that contains the three primary colors in each pixel

class Picture {
	private:
		vector<Pixel> pixels;
		int width;
		int height;
		int maxint;
	public:
		Picture();
		const Pixel& get_pixel(int row, int column) const;
		Pixel& get_pixel(int row, int column);
		void set_pixel(int row, int column, Pixel&);
		void invert();
		void flip_x();
		void flip_y();
		bool read_input(istream &in);
		void write_output(ostream &out);
};
// A class called Picture that cointans all the fucntions, vectorm and integer used in this program

int main(int argc, char *argv[]) {

	Picture pic;

	if (!(argc == 4 || argc == 3)) {
		cout << "Usage: ./lab12 <input file or '-'> <output or '-'> <I/X/Y/not specified>\n";
		return 1;
	}
    // if the command-line argument does not contain 3 or 4 elements, it will cout a proper command-line argument format and returns 1

	string input = argv[1];
    // if the second command-line argument is '-', the user will type in the information in the ppm file
	if (input == "-") {
		if (pic.read_input(cin) == false) {
			cout << "Wrong command\n";
			return 1;
		}
        // this makes sure what is inputed from cin is correct
	}

	else {
		ifstream filein;
		filein.open(input);
        // opens the input file
		if (filein.fail()) {
			cout << "The file " << input << " cannot be read.\n";
			return 1;
		}
        // if the input file cannot be opened, it returns 1
		if (pic.read_input(filein) == false) {
			cout << "The file " << input << " cannot be read.\n";
		}
        // if the input file cannot be opened, it returns 1

        
		filein.close();
        // closes the input file
	}

	if (argc == 4) {
        // This part of will only be come to use if there are 4 command line argument
	
		string instruction = argv[3];
		if (instruction == "I") {
			pic.invert();
		}
        // This will invert the image
		else if (instruction == "Y") {
			pic.flip_y();
		}
        // This will flip the image around the y-axis
		else if (instruction == "X") {
			pic.flip_x();
		}
        // This will flip the image around the x-axis

	}
	string output = argv[2];
	if (output == "-") {
		pic.write_output(cout);
	}
// if the third command-line argument is a dash, the ppm file information will be printed as cout
    
	else {
		ofstream fileout;
		fileout.open(output);
        // opens the output file

		if (fileout.fail()) {
			cout << "The file " << output << " cannot be opened.\n";
			return 1;
		}
        // if the output file cannot be opened, it will return 1

		pic.write_output(fileout);
        // prints out the ppm file information into an output file
        
		fileout.close();
        // closes the file

		return 0;

	
	}
}

Picture::Picture() {
	width = 0;
	height = 0;
	maxint = 0;
}
 // This sets the width, height, and the maximum intensity to 0 each time the class is created

const Pixel& Picture::get_pixel(int row, int column) const {

	int chosenposition;
	chosenposition = row*width + column;

	return pixels.at(chosenposition);
}
// This function takes the row and column of the pixel and directs it to the same pixel that is in the vector of pixels. This is an accessor.

Pixel& Picture::get_pixel(int row, int column) {

	int chosenposition;
	chosenposition = row*width + column;

	return pixels.at(chosenposition);
}
// This function takes the row and column of the pixel and directs it to the same pixel that is in the vector of pixels. This is an mutator.

void Picture::set_pixel(int row, int column, Pixel& p) {
	get_pixel(row, column) = p;
}
// This takes the row and column of a pixel and assigns it into the vector of pixels

void Picture::invert() {
	Pixel p;

	for(int h = 0; h < height; ++h) {
		for (int w = 0; w < width; ++w) {
			p.red = maxint - get_pixel(h,w).red;
			p.green = maxint - get_pixel(h,w).green;
			p.blue = maxint - get_pixel(h,w).blue;
			set_pixel(h,w,p);
		}
	}
	// this flips the intensity of each pixel by taking each pixels and subtracting the intensity value from the maximum intensity

}

void Picture::flip_y() {

	Pixel temp1, temp2;
	for (int h = 0; h < height; ++h) {
		for (int w = 0; w < width/2; ++w) {
			temp1 = get_pixel(h,w);
			temp2 = get_pixel(h,width-w-1);
			set_pixel(h,width-w-1,temp1);
			set_pixel(h,w,temp2);
		}	
	}

}
    // This flips the image around the y axis by assigning the pixel value that is in the same position but in the opposite side of the axis.

void Picture::flip_x() {
	Pixel temp1, temp2;

	for (int w = 0; w < width; ++w) {
		for (int h = 0; h < height/2; ++h) {
			temp1 = get_pixel(h,w);
			temp2 = get_pixel(height-h-1,w);
			set_pixel(height-h-1,w,temp1);
			set_pixel(h,w,temp2);
		}
	}
}
// This flips the image around the x axis by assigning the pixel value that is in the same position but in the opposite side of the axis.


bool Picture::read_input(istream &in) {
	bool readpix = false; 

	Pixel p;

	stringstream ss;
	string name;
	string type;
	char first;

	getline(in,name);
	first = name.at(0);

	while(first == '#') {
		getline(in,name);
		first = name.at(0);
    }
    // This allows the comments to be ignored until the line with the type of ppm file is reached

	ss << name;
	ss >> type;
	if (type != "P3") {
		cout << "Wrong file type\n";
		return 1;
	}
    // makes sure the ppm file is correct. If not, returns 1

	ss.clear();

	getline(in,name);
	first = name.at(0);

	while(first == '#') {
		getline(in,name);
		first = name.at(0);
	}
    // This allows the comments to be ignored until the line with the width and heigh of ppm file is reached

	ss << name;
	ss >> width >> height;
    // assigns the width and the heigt
	ss.clear();

	pixels.reserve(height*width);
    // reserves the amount of width*height space in the vector

	getline(in,name);
	first = name.at(0);

	while(first == '#') {
		getline(in,name);
		first = name.at(0);
	}
    // This allows the comments to be ignored until the line with the maximum intesity of ppm file is reached

	ss << name;
	ss >> maxint;
    // assigns the maximum intensity
	ss.clear();

	for (int i = 0; i < width*height; ++i) {
		do {
			getline(in,name);
			first = name.at(0);
		}
		while (first == '#');
        // This allows the comments to be ignored until the line with the pixel information of ppm file is reached


		ss << name;
		if (!(ss >> p.red >> p.green >> p.blue)) {
			cout << "Missing pixel\n";
			return 1;
		}
		// makes sures each pixel has red, green, and blue in it. If it does not, it returns 1

		pixels.push_back(p);
        // gets the pixel information into the vector
		ss.clear();
	}

	if (width*height > pixels.size()) {
		cout << "Not enough pixels\n";
		return 1;
	}
	// makes sure that there is actually enough pixels to read in. If it does not, it returns 1.
	readpix = true;

	return readpix;
}

void Picture::write_output(ostream &out) {

	out << "P3\n";
	out << width << " " << height << endl;
	out << maxint << endl;

	for (int i = 0; i < pixels.size(); ++i) {
		out << pixels.at(i).red << " " << pixels.at(i).green << " " << pixels.at(i).blue << endl;
	}
	// This outputs the information in a ppm format. The command line argument will specify wether if it will be outputed in a file or cout
}
