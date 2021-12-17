#include "Entity.h"
Entity::Entity() {
	flag = false;
	dx = dy = 0;
	orientation = direction::still;
}
Entity::Entity(int px, int py, int pw, int ph) {
	x = px;
	y = py;
	w = pw;
	h = ph;
	flag = false;
	dx = dy = 0;
	orientation = direction::still;
}
Entity::Entity(int px, int py, int pw, int ph, int psprite_rows, int psprite_columns, int pcurrent_row, int pcurrent_column) {
	x = px;
	y = py;
	w = pw;
	h = ph;
	sprite_rows = psprite_rows;
	sprite_columns = psprite_columns;
	current_row = pcurrent_row;
	current_column = pcurrent_column;
	flag = false;
	dx = dy = 0;
	orientation = direction::still;
}
Entity::~Entity() {}

void Entity::new_x(int new_data) { x = new_data; }
void Entity::new_y(int new_data) { y = new_data; }
void Entity::new_w(int new_data) { w = new_data; }
void Entity::new_h(int new_data) { h = new_data; }
void Entity::new_dx(int new_data) { dx = new_data; }
void Entity::new_dy(int new_data) { dy = new_data; }
void Entity::new_horizontal_velocity(int new_data) { horizontal_velocity = new_data; }
void Entity::new_vertical_velocity(int new_data) { vertical_velocity = new_data; }
void Entity::new_sprite_rows(int new_data) { sprite_rows = new_data; }
void Entity::new_sprite_columns(int new_data) { sprite_columns = new_data; }
void Entity::new_current_column(int new_data) { current_column = new_data; }
void Entity::new_current_row(int new_data) { current_row = new_data; }
void Entity::new_flag(bool new_data) { flag = new_data; }
void Entity::new_orientation(direction new_data) {
	orientation = new_data;

	if (orientation == direction::up) { dy = -vertical_velocity; dx = 0; current_row = 3; }
	if (orientation == direction::down) { dy = vertical_velocity; dx = 0; current_row = 0; }
	if (orientation == direction::left) { dx = -horizontal_velocity; dy = 0; current_row = 1; }
	if (orientation == direction::right) { dx = horizontal_velocity; dy = 0; current_row = 2; }

	if (orientation == direction::still) { dx = 0; dy = 0; current_row = 0; current_column = 0; }
}

int Entity::return_x() { return x; }
int Entity::return_y() { return y; }
int Entity::return_w() { return w; }
int Entity::return_h() { return h; }
int Entity::return_dx() { return dx; }
int Entity::return_dy() { return dy; }
int Entity::return_horizontal_velocity() { return horizontal_velocity; }
int Entity::return_vertical_velocity() { return vertical_velocity; }
int Entity::return_sprite_rows() { return sprite_rows; }
int Entity::return_sprite_columns() { return sprite_columns; }
int Entity::return_current_column() { return current_column; }
int Entity::return_current_row() { return current_row; }
bool Entity::return_flag() { return flag; }
direction Entity::return_orientation() { return orientation; }
Rectangle Entity::return_rectangle() { return Rectangle(x, y, w, h); }

void Entity::Move(Graphics^ g) {
	if (x + dx < 1 || x + dx + w > g->VisibleClipBounds.Width) {
		dx = 0;
		flag = true;
	}
	if (y + dy < 1 || y + dy + h > g->VisibleClipBounds.Height) {
		dy = 0;
		flag = true;
	}	
	x += dx;
	y += dy;
}
void Entity::Draw_from_image(Graphics^ g, Bitmap^ bmp) {
	//Giving the entity the same width and height as the image shown
	w = bmp->Width / sprite_columns;
	h = bmp->Height / sprite_rows;
	Rectangle portion = Rectangle(current_column * w, current_row * h, w, h);
	//Printing
	g->DrawImage(bmp, x, y, portion, GraphicsUnit::Pixel);
	current_column++;
	if (current_column >= sprite_columns) current_column = 0;
}
vector<string> Entity::Read_file() {
	string line;
	vector<string> result;
	ifstream myFile("config.txt");
	if (!myFile.fail()) {
		while (!myFile.eof()) {
			getline(myFile, line);
			result.push_back(line);
		}
		myFile.close();
	}
	return result;
}
void Entity::Record_file(vector<string> new_data) {
	ofstream myFile("config.txt");  // TO ERASE PREVIOUS FILE BEFORE SAVING DATA
	//ofstream myFile("OUTPUT.TXT",std::ofstream::app);  // TO NOT ERASE PREVIOUS FILE BEFORE SAVING DATA
	if (!myFile.fail()) {
		for (int i = 0; i < new_data.size(); i++)
			myFile << new_data.at(i) << "\n";
		myFile.flush();
		myFile.close();
	}
}
