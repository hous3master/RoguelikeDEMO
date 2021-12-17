#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace System::Drawing;
public enum direction { up, down, left, right, still };
class Entity
{
protected:
	int x, y; //LOCATION: Cardinal position
	int w, h; //SIZE: Width and height
	int dx, dy, vertical_velocity, horizontal_velocity; //MOVEMENT: X determinant, Y determinant, vertical velocity and horizontal_velocity 
	bool flag;
	direction orientation;
	int sprite_rows, sprite_columns, current_column, current_row;
public:
	Entity();
	Entity(int px, int py, int pw, int ph);
	Entity(int px, int py, int pw, int ph, int psprite_rows, int psprite_column, int pcolumn, int prow);
	~Entity();

	void new_x(int new_data);
	void new_y(int new_data);
	void new_w(int new_data);
	void new_h(int new_data);
	void new_dx(int new_data);
	void new_dy(int new_data);
	void new_horizontal_velocity(int new_data);
	void new_vertical_velocity(int new_data);
	void new_sprite_rows(int new_data);
	void new_sprite_columns(int new_data);
	void new_current_column(int new_data);
	void new_current_row(int new_data);
	void new_flag(bool new_data);
	void new_orientation(direction new_data);

	int return_x();
	int return_y();
	int return_w();
	int return_h();
	int return_dx();
	int return_dy();
	int return_horizontal_velocity();
	int return_vertical_velocity();
	int return_sprite_rows();
	int return_sprite_columns();
	int return_current_column();
	int return_current_row();
	bool return_flag();
	direction return_orientation();
	Rectangle return_rectangle();

	virtual void Move(Graphics^ g);
	virtual void Draw_from_image(Graphics^ g, Bitmap^ bmp);

	vector<string> Read_file();
	void Record_file(vector<string> datos);
};

