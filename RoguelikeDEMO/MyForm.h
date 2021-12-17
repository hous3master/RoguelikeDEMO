#pragma once
#include "Game.h"
namespace RoguelikeDEMO {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			objGame = new Game();
			bmpPlayer = gcnew Bitmap("player.png");
			bmpGhost = gcnew Bitmap("ghost.png");
			bmpFireball = gcnew Bitmap("fireball.png");
			bmpBG = gcnew Bitmap("background.png");
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		Game* objGame;
		Bitmap^ bmpPlayer;
		Bitmap^ bmpGhost;
		Bitmap^ bmpBG;
	private: System::Windows::Forms::Label^ label_lifes;
	private: System::Windows::Forms::Label^ label_points;
	private: System::Windows::Forms::Label^ label_instructions;
		   Bitmap^ bmpFireball;
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->label_lifes = (gcnew System::Windows::Forms::Label());
			this->label_points = (gcnew System::Windows::Forms::Label());
			this->label_instructions = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// label_lifes
			// 
			this->label_lifes->AutoSize = true;
			this->label_lifes->BackColor = System::Drawing::Color::Transparent;
			this->label_lifes->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_lifes->Location = System::Drawing::Point(576, 9);
			this->label_lifes->Name = L"label_lifes";
			this->label_lifes->Size = System::Drawing::Size(184, 25);
			this->label_lifes->TabIndex = 0;
			this->label_lifes->Text = L"LIFESplaceholder";
			// 
			// label_points
			// 
			this->label_points->AutoSize = true;
			this->label_points->BackColor = System::Drawing::Color::Transparent;
			this->label_points->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_points->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->label_points->Location = System::Drawing::Point(576, 50);
			this->label_points->Name = L"label_points";
			this->label_points->Size = System::Drawing::Size(256, 31);
			this->label_points->TabIndex = 1;
			this->label_points->Text = L"POINTSplaceholder";
			// 
			// label_instructions
			// 
			this->label_instructions->AutoSize = true;
			this->label_instructions->BackColor = System::Drawing::Color::Transparent;
			this->label_instructions->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label_instructions->Location = System::Drawing::Point(12, 9);
			this->label_instructions->Name = L"label_instructions";
			this->label_instructions->Size = System::Drawing::Size(399, 25);
			this->label_instructions->TabIndex = 2;
			this->label_instructions->Text = L"Move with WASD and shoot with mouseclick";
			this->label_instructions->Click += gcnew System::EventHandler(this, &MyForm::label_instructions_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(782, 753);
			this->Controls->Add(this->label_instructions);
			this->Controls->Add(this->label_points);
			this->Controls->Add(this->label_lifes);
			this->MaximumSize = System::Drawing::Size(800, 800);
			this->MinimumSize = System::Drawing::Size(800, 800);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseClick);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		//BACKGROUND
		Graphics^ g = CreateGraphics();
		BufferedGraphicsContext^ space = BufferedGraphicsManager::Current;
		BufferedGraphics^ bf = space->Allocate(g, ClientRectangle);
		//bf->Graphics->Clear(Color::White); //Solid color
		bf->Graphics->DrawImage(bmpBG, 0, 0, bmpBG->Width, bmpBG->Height); //Custom BG
		
		//Execution
		objGame->Draw_Player(bf->Graphics, bmpPlayer);
		objGame->Draw_Vector(bf->Graphics, bmpGhost, bmpFireball);
		objGame->Insert_Ghosts();
		objGame->Colision();
		if (objGame->End_Game())
			timer1->Enabled = false;
		label_lifes->Text = objGame->return_text_lifes();
		label_points->Text = objGame->return_text_points();

		bf->Render(g);
		delete bf, space, g;
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::A) objGame->new_orientation(direction::left);
		if (e->KeyCode == Keys::D) objGame->new_orientation(direction::right);
		if (e->KeyCode == Keys::W) objGame->new_orientation(direction::up);
		if (e->KeyCode == Keys::S) objGame->new_orientation(direction::down);
	}
	private: System::Void MyForm_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		objGame->Shoot();
	}
	private: System::Void label_instructions_Click(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
