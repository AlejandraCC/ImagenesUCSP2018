#pragma once 
#include"opencv2\highgui\highgui.hpp" // lee las imagenes y las  muestra
#include"opencv2\imgproc.hpp"  // permite usar el canny para identificar los contornos
//#include <cv.h>
//#include <highgui.h>
#include <math.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include<opencv2\imgcodecs\imgcodecs.hpp>
#include <opencv2/opencv.hpp>
#include <omp.h>
#include<vector>
#include<algorithm>
//#include <iostream>
#include <complex>
//#include <iostream>
#include <valarray>
/*

using namespace cv;
using namespace std;

void pixelate(Mat& src, Mat& dst, int pixel_size = 1);
void pixelate(Mat& src, Mat& dst, Rect roi, int pixel_size = 1);
void ontrack(int value, void* data);

*/

namespace testForm_opencv {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Runtime::InteropServices;

	using namespace cv;
	using namespace std;

	Mat image;
	Mat convolucion = (Mat_<int>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);
	//Mat mascara = (Mat_<int>(3, 3) << 1,2,1,2,4,2,1,2,1);
	Mat mascara = (Mat_<int>(3, 3) << -2, -1, 0, -1, 1, 1, 0, 1, 2);
	//Mat mascara = (Mat_<int>(3, 3) << -1, -2, 1, 0, 0, 0, 1, 1, 1);
	Mat kernel = (Mat_<char>(3, 3) << 0, 1, 0,
		1, -4, 1,
		0, 1, 0);
	Mat mediana;

	int h = 110, r = 40;

	/// <summary>
	/// Resumen de MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  b_buscar;
	protected private: System::Windows::Forms::Button^  btn_mitad;
	private:

	private:


	private: System::Windows::Forms::PictureBox^  box_image;
	protected private: System::Windows::Forms::Button^  b_gris;
	protected private: System::Windows::Forms::Button^  b_redim_doble;
	protected private: System::Windows::Forms::Button^  button1;
	protected private: System::Windows::Forms::Button^  button2;
	protected private: System::Windows::Forms::Button^  button3;
	protected private: System::Windows::Forms::Button^  button4;
	protected private: System::Windows::Forms::Button^  button5;
	protected private: System::Windows::Forms::Button^  button6;
	protected private: System::Windows::Forms::Button^  button7;
	private: System::Windows::Forms::TrackBar^  trackBar1;
	protected private:
	private: System::Windows::Forms::TrackBar^  trackBar2;
	private: System::Windows::Forms::Label^  Dilatación;
	private: System::Windows::Forms::Label^  label1;






	private:

	private:

	protected:

	protected:

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->b_buscar = (gcnew System::Windows::Forms::Button());
			this->btn_mitad = (gcnew System::Windows::Forms::Button());
			this->box_image = (gcnew System::Windows::Forms::PictureBox());
			this->b_gris = (gcnew System::Windows::Forms::Button());
			this->b_redim_doble = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			this->Dilatación = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box_image))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			this->SuspendLayout();
			// 
			// b_buscar
			// 
			this->b_buscar->Location = System::Drawing::Point(485, 12);
			this->b_buscar->Name = L"b_buscar";
			this->b_buscar->Size = System::Drawing::Size(150, 29);
			this->b_buscar->TabIndex = 0;
			this->b_buscar->Text = L"Buscar";
			this->b_buscar->UseVisualStyleBackColor = true;
			this->b_buscar->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// btn_mitad
			// 
			this->btn_mitad->Location = System::Drawing::Point(485, 56);
			this->btn_mitad->Name = L"btn_mitad";
			this->btn_mitad->Size = System::Drawing::Size(150, 35);
			this->btn_mitad->TabIndex = 1;
			this->btn_mitad->Text = L"Redimensionar a la mitad";
			this->btn_mitad->UseVisualStyleBackColor = true;
			this->btn_mitad->Click += gcnew System::EventHandler(this, &MainForm::button1_Click_1);
			// 
			// box_image
			// 
			this->box_image->Location = System::Drawing::Point(12, 12);
			this->box_image->Name = L"box_image";
			this->box_image->Size = System::Drawing::Size(445, 360);
			this->box_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->box_image->TabIndex = 2;
			this->box_image->TabStop = false;
			this->box_image->Click += gcnew System::EventHandler(this, &MainForm::pictureBox1_Click);
			// 
			// b_gris
			// 
			this->b_gris->Location = System::Drawing::Point(485, 161);
			this->b_gris->Name = L"b_gris";
			this->b_gris->Size = System::Drawing::Size(150, 35);
			this->b_gris->TabIndex = 3;
			this->b_gris->Text = L"Cambiar Gris";
			this->b_gris->UseVisualStyleBackColor = true;
			this->b_gris->Click += gcnew System::EventHandler(this, &MainForm::button1_Click_2);
			// 
			// b_redim_doble
			// 
			this->b_redim_doble->Location = System::Drawing::Point(485, 107);
			this->b_redim_doble->Name = L"b_redim_doble";
			this->b_redim_doble->Size = System::Drawing::Size(150, 35);
			this->b_redim_doble->TabIndex = 4;
			this->b_redim_doble->Text = L"Redimensionar al doble";
			this->b_redim_doble->UseVisualStyleBackColor = true;
			this->b_redim_doble->Click += gcnew System::EventHandler(this, &MainForm::button1_Click_3);
			// 
			// button1
			// 
			this->button1->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button1->Location = System::Drawing::Point(485, 214);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(150, 35);
			this->button1->TabIndex = 5;
			this->button1->Text = L"Convolucion";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click_4);
			// 
			// button2
			// 
			this->button2->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button2->Location = System::Drawing::Point(485, 255);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(150, 35);
			this->button2->TabIndex = 6;
			this->button2->Text = L"sal y pimienta";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button3->Location = System::Drawing::Point(485, 296);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(150, 35);
			this->button3->TabIndex = 7;
			this->button3->Text = L"Rotar";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button4->Location = System::Drawing::Point(485, 346);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(150, 35);
			this->button4->TabIndex = 8;
			this->button4->Text = L"Mediana";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// button5
			// 
			this->button5->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button5->Location = System::Drawing::Point(382, 387);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(150, 35);
			this->button5->TabIndex = 9;
			this->button5->Text = L"Fourier";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &MainForm::button5_Click);
			// 
			// button6
			// 
			this->button6->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button6->Location = System::Drawing::Point(12, 387);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(150, 35);
			this->button6->TabIndex = 10;
			this->button6->Text = L"Ecualizar Imagen";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &MainForm::button6_Click);
			// 
			// button7
			// 
			this->button7->Cursor = System::Windows::Forms::Cursors::Cross;
			this->button7->Location = System::Drawing::Point(200, 387);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(150, 35);
			this->button7->TabIndex = 11;
			this->button7->Text = L"Borde";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MainForm::button7_Click);
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(60, 428);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(104, 45);
			this->trackBar1->TabIndex = 12;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &MainForm::trackBar1_Scroll);
			// 
			// trackBar2
			// 
			this->trackBar2->Location = System::Drawing::Point(268, 428);
			this->trackBar2->Name = L"trackBar2";
			this->trackBar2->Size = System::Drawing::Size(104, 45);
			this->trackBar2->TabIndex = 13;
			this->trackBar2->Scroll += gcnew System::EventHandler(this, &MainForm::trackBar2_Scroll);
			// 
			// Dilatación
			// 
			this->Dilatación->AutoSize = true;
			this->Dilatación->Location = System::Drawing::Point(197, 431);
			this->Dilatación->Name = L"Dilatación";
			this->Dilatación->Size = System::Drawing::Size(54, 13);
			this->Dilatación->TabIndex = 20;
			this->Dilatación->Text = L"Dilatación";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 431);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(42, 13);
			this->label1->TabIndex = 21;
			this->label1->Text = L"Erosión";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(658, 494);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->Dilatación);
			this->Controls->Add(this->trackBar2);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->b_redim_doble);
			this->Controls->Add(this->b_gris);
			this->Controls->Add(this->box_image);
			this->Controls->Add(this->btn_mitad);
			this->Controls->Add(this->b_buscar);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->box_image))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		cout << "hola";
		// Displays an OpenFileDialog so the user can select a Cursor.
		OpenFileDialog ^ openFileDialog1 = gcnew OpenFileDialog();
		openFileDialog1->Filter = "Image(*.bmp)|*.bmp;";

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::Cancel)
		{
			return;
		}
		Bitmap ^bmp_img = gcnew Bitmap(openFileDialog1->FileName);
		box_image->Image = bmp_img;
		box_image->Refresh();

		image = imread(convertir_string(openFileDialog1->FileName));


	}
	private: char*convertir_string(System::String^str) {
		char* strs = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
		return strs;
	}
	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
	}

	private: System::Void b_redi_mitad(System::Object^  sender, System::EventArgs^  e) {

		cout << image.size() << endl;


		if (image.empty()) //pregunta si la imagen fue recibida correctamente
		{
			cout << "Error : Imagen no pudo ser abierta!!" << endl;

		}
		else {

			float ratio = 0.5;
			Mat image_100(image.rows*ratio, image.cols*ratio, CV_8UC3);

			//int n_col_ratio = cvRound(image.cols*ratio);
			//float salto = (float)image.cols / (float)n_col_ratio;
			//float centro = salto / 2;
			cout << image_100.cols;
			double start = (double)getTickCount();

			//resize(image, image_100, cv::Size(image.cols * 2, image.rows *2), 0, 0, CV_INTER_CUBIC);
#pragma omp parallel for
			for (int i = 0; i < image_100.rows; i++) {

				float posx = i / ratio;
				int predx = floor(posx);

				for (int j = 0; j < image_100.cols; j++) {

					//float pos = (j*salto) + centro;
					float pos = j / ratio;


					int pred = floor(pos);
					//int suss = ceil(pos);

					//float d_pre = pos - pred;
					//float d_suss = suss - pos;
					//int val_pre = image.at<uchar>(predx, pred);
					//int val_sus = image.at<uchar>(i, suss);

					//float val = (val_pre*d_suss) + (val_sus*d_pre);
					//int i_val = cvRound(val_pre);

					//if (i_val == 0)
					//i_val = val_pre;

					image_100.at<Vec3b>(i, j) = image.at<Vec3b>(predx, pred);


				}
			}
			double elapsed = ((double)getTickCount() - start) / getTickFrequency();


			namedWindow("Escalada a la mitad", CV_WINDOW_AUTOSIZE); //creamos una ventana 
			imshow("Escalada a la mitad", image_100); //mostramos la imagen original


		}
	}

	private: System::Void button1_Click_2(System::Object^  sender, System::EventArgs^  e) {

		Mat image_100(image.rows, image.cols, CV_8UC1);
		int columnas = image.cols;
		int filas = image.rows;

		for (int i = 0; i < image.rows; i++) {
			for (int j = 0; j < image.cols; j++) {
				//uchar pixel2 = image.at<uchar>(i, j);
				//cout << (int)pixel2<<endl;
				Vec3b pixel = image.at<Vec3b>(i, j);

				uchar B = pixel[0];
				uchar G = pixel[1];
				uchar R = pixel[2];

				image_100.at<uchar>(i, j) = (B + G + R) / 3;

			}
		}



		namedWindow("Original", CV_WINDOW_AUTOSIZE); //creamos una ventana 
		imshow("Original", image); //mostramos la imagen original

		Mat image_gris;

		cvtColor(image, image_gris, CV_BGR2GRAY); // cambiamos la imagen a escala de grises

		namedWindow("Gris", CV_WINDOW_AUTOSIZE); //creamos una ventana 
		imshow("Gris", image_gris); //mostramos la imagen original

	}
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) {
		cout << image.size() << endl;


		if (image.empty()) //pregunta si la imagen fue recibida correctamente
		{
			cout << "Error : Imagen no pudo ser abierta!!" << endl;

		}
		else {

			float ratio = 0.5;
			Mat image_100(image.rows*ratio, image.cols*ratio, CV_8UC3);

			cout << image_100.cols;
			double start = (double)getTickCount();

			//resize(image, image_100, cv::Size(image.cols * 2, image.rows *2), 0, 0, CV_INTER_CUBIC);
#		pragma omp parallel for
			for (int i = 0; i < image_100.rows; i++) {

				float posx = i / ratio;
				int predx = floor(posx);

				for (int j = 0; j < image_100.cols; j++) {

					float pos = j / ratio;
					int pred = floor(pos);


					image_100.at<Vec3b>(i, j) = image.at<Vec3b>(predx, pred);


				}
			}
			double elapsed = ((double)getTickCount() - start) / getTickFrequency();
			cout << "tiempo en redimensionar" << elapsed << endl;

			namedWindow("Escalada a la mitad", CV_WINDOW_AUTOSIZE); //creamos una ventana 
			imshow("Escalada a la mitad", image_100); //mostramos la imagen original

			for (size_t i = 0; i < 4; i++)
			{
				pyrDown(image_100, image_100);
				imshow(to_string(image_100.size().width), image_100);
			}


		}

	}
	private: System::Void button1_Click_3(System::Object^  sender, System::EventArgs^  e) {

		cout << image.size() << endl;


		if (image.empty()) //pregunta si la imagen fue recibida correctamente
		{
			cout << "Error : Imagen no pudo ser abierta!!" << endl;

		}
		else {

			float ratio = 2;
			Mat image_100(image.rows*ratio, image.cols*ratio, CV_8UC3);

			//int n_col_ratio = cvRound(image.cols*ratio);
			//float salto = (float)image.cols / (float)n_col_ratio;
			//float centro = salto / 2;
			cout << image_100.cols;
			double start = (double)getTickCount();

			//resize(image, image_100, cv::Size(image.cols * 2, image.rows *2), 0, 0, CV_INTER_CUBIC);
#		pragma omp parallel for
			for (int i = 0; i < image_100.rows; i++) {

				float posx = i / ratio;
				int predx = floor(posx);

				for (int j = 0; j < image_100.cols; j++) {

					//float pos = (j*salto) + centro;
					float pos = j / ratio;


					int pred = floor(pos);
					//int suss = ceil(pos);

					//float d_pre = pos - pred;
					//float d_suss = suss - pos;
					//int val_pre = image.at<uchar>(predx, pred);
					//int val_sus = image.at<uchar>(i, suss);

					//float val = (val_pre*d_suss) + (val_sus*d_pre);
					//int i_val = cvRound(val_pre);

					//if (i_val == 0)
					//i_val = val_pre;

					image_100.at<Vec3b>(i, j) = image.at<Vec3b>(predx, pred);


				}
			}
			double elapsed = ((double)getTickCount() - start) / getTickFrequency();
			cout << "tiempo en redimensionar" << elapsed << endl;

			namedWindow("Escalada al doble", CV_WINDOW_AUTOSIZE); //creamos una ventana 
			imshow("Escalada al doble", image_100); //mostramos la imagen original



		}

	}
	private: System::Void b_guardar_Click(System::Object^  sender, System::EventArgs^  e) {


	}
	private: System::Void button1_Click_4(System::Object^  sender, System::EventArgs^  e) {
		cout << "C = " << endl << " " << convolucion << endl << endl;

		if (image.empty()) //pregunta si la imagen fue recibida correctamente
		{
			cout << "Error : Imagen no pudo ser abierta!!" << endl;

		}
		else {
			Mat image2 = image;
			Mat image3 = image;
			Mat salida2 = image;
			Mat salida3 = image;

			Mat salida = Mat::zeros(image.rows, image.cols, CV_8UC3);
			int mas_fil = mascara.rows / 2;
			int mas_col = mascara.cols / 2;

			Mat aux = Mat::zeros(image2.rows + 2 * mas_fil, image2.cols + 2 * mas_col, CV_8UC3);
			Mat ROI = aux(Rect(mas_col, mas_fil, image2.cols, image2.rows));

			image2.copyTo(ROI);

			/*
			for (int r = mas_fil; r < aux.rows - mas_fil; r++) {
			for (size_t c = mas_col	; c < aux.cols-mas_col; c++)
			{
			Vec3b accum = 0.0;

			for (size_t m_r = 0; m_r < mas_fil; m_r++)
			{
			for (size_t m_c = 0; m_c < mas_col; m_c++)
			{
			accum += aux.at<Vec3b>(r + m_r - mas_fil, c + m_c - mas_col)*mascara.at<Vec3b>(m_r, m_c);
			}
			}
			salida.at<Vec3b>(r - mas_fil, c - mas_col) = accum;
			}
			}
			*/
			/*
			for (int i = 0; i < image.rows; i++) {
			for (int j = 0; j < image.cols; j++) {
			//uchar pixel2 = image.at<uchar>(i, j);
			//cout << (int)pixel2<<endl;
			Vec3b pixel = image.at<Vec3b>(i, j);

			uchar B = pixel[0];
			uchar G = pixel[1];
			uchar R = pixel[2];

			image_100.at<uchar>(i, j) = (B + G + R) / 3;

			}
			*/
			filter2D(image2, salida2, image2.depth(), mascara);
			namedWindow("convolucion", CV_WINDOW_AUTOSIZE); //creamos una ventana 
			imshow("convolucion", salida2); //mostramos la imagen original
											/*
											filter2D(image3, salida3, image3.depth(), convolucion);
											namedWindow("convolucion2", CV_WINDOW_AUTOSIZE); //creamos una ventana
											imshow("convolucion2", salida3); //mostramos la imagen original
											*/
		}


	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		Mat sp_img = image;
		int z = 10000;
		int j, i;
		int colores = image.channels();
		if (colores == 3) {
			for (int x = 0; x < z; x++) {
				i = rand() % sp_img.rows;
				j = rand() % sp_img.cols;
				int r = rand() % 2;
				if (r == 1) {
					sp_img.at<Vec3b>(i, j)[0] = 255;
					sp_img.at<Vec3b>(i, j)[1] = 255;
					sp_img.at<Vec3b>(i, j)[2] = 255;
				}
				else {
					sp_img.at<Vec3b>(i, j)[0] = 0;
					sp_img.at<Vec3b>(i, j)[1] = 0;
					sp_img.at<Vec3b>(i, j)[2] = 0;
				}
			}
		}
		else if (colores == 1) {
			for (int k = 0; k < z; k++) {
				i = rand() % sp_img.rows;
				j = rand() % sp_img.cols;
				int r = rand() % 2;
				if (r == 1) {
					sp_img.at<uchar>(i, j) = 255;
				}
				else {
					sp_img.at<uchar>(i, j) = 0;
				}
			}
		}
		namedWindow("Sal y Pimienta", CV_WINDOW_AUTOSIZE); //creamos una ventana
		imshow("Sal y Pimienta", sp_img);
		mediana = sp_img;

	}
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		Mat rotar = image;
		Mat salidar;
		const double degrees = 45;
		cv::Point2f center(rotar.cols / 2.0, rotar.rows / 2.0);
		cv::Mat rot = cv::getRotationMatrix2D(center, degrees, 1.0);
		cv::Rect bbox = cv::RotatedRect(center, rotar.size(), degrees).boundingRect();

		rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
		rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

		cv::warpAffine(rotar, salidar, rot, bbox.size());

		namedWindow("rotar", CV_WINDOW_AUTOSIZE); //creamos una ventana
		imshow("rotar", salidar);
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
		Mat mm = mediana;
		Mat salidam = image;
		#pragma omp parallel for
		for (int i = 1; i < mm.rows - 1; i++) {

			for (int j = 1; j < mm.cols - 1; j++) {
				//uchar pixel2 = image.at<uchar>(i, j);
				//cout << (int)pixel2<<endl;

				vector<uchar> rr, gg, bb;
				
				for (size_t ii = i - 1; ii < i + 2; ii++)
				{
					for (size_t jj = j - 1; jj < j + 2; jj++)
					{
						Vec3b pixel = mm.at<Vec3b>(ii, jj);

						rr.push_back(pixel[0]);
						gg.push_back(pixel[1]);
						bb.push_back(pixel[2]);
					}
				}
				sort(rr.begin(), rr.end());
				sort(gg.begin(), gg.end());
				sort(bb.begin(), bb.end());

				Vec3b pixelsa;
				pixelsa[0] = rr[4];
				pixelsa[1] = gg[4];
				pixelsa[2] = bb[4];

				salidam.at<Vec3b>(i, j) = pixelsa;
			}
		}
		namedWindow("mediana", CV_WINDOW_AUTOSIZE); //creamos una ventana
		imshow("mediana", salidam);

	}

	private: System::Void button5_Click(System::Object^  sender, System::EventArgs^  e) {

		// fourier
		Mat Imae = image;

		imwrite("test.jpg", Imae);
		Mat I = imread("test.jpg", CV_LOAD_IMAGE_GRAYSCALE);
		//Mat I;
		//cvtColor(imaag, I, CV_BGR2BGRA);

		Mat padded;                            //expand input image to optimal size
		int m = getOptimalDFTSize(I.rows);
		int n = getOptimalDFTSize(I.cols); // on the border add zero values
		copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));

		Mat planes[] = { Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F) };
		Mat complexI;
		merge(planes, 2, complexI);         // Add to the expanded another plane with zeros

		dft(complexI, complexI);            // this way the result may fit in the source matrix

		split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
		magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
		Mat magI = planes[0];

		magI += Scalar::all(1);                    // switch to logarithmic scale
		log(magI, magI);

		// crop the spectrum, if it has an odd number of rows or columns
		magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

		// rearrange the quadrants of Fourier image  so that the origin is at the image center
		int cx = magI.cols / 2;
		int cy = magI.rows / 2;

		Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
		Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
		Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
		Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

		Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
		q0.copyTo(tmp);
		q3.copyTo(q0);
		tmp.copyTo(q3);

		q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
		q2.copyTo(q1);
		tmp.copyTo(q2);

		normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
												// viewable image form (float between values 0 and 1).

		imshow("Entrada", I);    // Show the result
		imshow("Espectro fourier", magI);
		waitKey();

	}

			 void drawLine(Mat histImage, int bin_w, int i, int height, Mat b_hist, Scalar color) {
				 line(histImage,
					 cv::Point(bin_w*(i - 1), height - cvRound(b_hist.at<float>(i - 1))),
					 cv::Point(bin_w*(i), height - cvRound(b_hist.at<float>(i))),
					 color);
			 }

			 void drawHistogram(cv::InputArray img)
			 {
				 // Dividir los canales BRG
				 vector<Mat> bgr;
				 split(img, bgr);

				 // Crear un histograma con 256 bin (numero de subdivisiones) uno por pixel [0..256]
				 int numbins = 256;

				 // Establecer rango para los canales (B, G, R)
				 float range[] = { 0, 256 };
				 const float* histRange = { range };

				 Mat b_hist, g_hist, r_hist;

				 // Calcular el histograma para cada canal
				 calcHist(&bgr[0], 1, 0, Mat(), b_hist, 1, &numbins, &histRange);
				 calcHist(&bgr[1], 1, 0, Mat(), g_hist, 1, &numbins, &histRange);
				 calcHist(&bgr[2], 1, 0, Mat(), r_hist, 1, &numbins, &histRange);

				 // Tamano del histograma
				 int h_width = 512;
				 int h_height = 400;

				 // Crear una imagen para dibujar en ella
				 Mat histImage(h_height, h_width, CV_8UC3, Scalar(20, 20, 20));

				 // Normalizar los histogramas 
				 normalize(b_hist, b_hist, 0, h_height, NORM_MINMAX);
				 normalize(g_hist, g_hist, 0, h_height, NORM_MINMAX);
				 normalize(r_hist, r_hist, 0, h_height, NORM_MINMAX);

				 int bin_width = cvRound((float)h_width / (float)numbins);

				 // Dibujar cada una de las lineas
				 for (int i = 1; i < numbins; i++)
				 {
					 drawLine(histImage, bin_width, i, h_height, b_hist, Scalar(255, 0, 0));
					 drawLine(histImage, bin_width, i, h_height, g_hist, Scalar(0, 255, 0));
					 drawLine(histImage, bin_width, i, h_height, r_hist, Scalar(0, 0, 255));
				 }

				 // Mostrar el histograma
				 imshow("Histograma BGR", histImage);
			 }

			 void equalizeColorImage(cv::InputArray src, cv::OutputArray dst)
			 {
				 // Convertir BGR image a YCrCb
				 Mat ycrcb;
				 cvtColor(src, ycrcb, COLOR_BGR2YCrCb);

				 // Extarer cada uno de los canales
				 vector<Mat> channels;
				 split(ycrcb, channels);

				 // Ecualizar histograma del canal Y (luminosidad) 
				 equalizeHist(channels[0], channels[0]);

				 // Unir los canales nuevamente
				 merge(channels, ycrcb);

				 // Convertir color YCrCb a BGR
				 cvtColor(ycrcb, dst, COLOR_YCrCb2BGR);
			 }


	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {

		Mat imageen = image;
		Mat salida, salida2;

		equalizeColorImage(imageen, salida);
		drawHistogram(imageen);

		//// convertir en escala de grises y ecualizar histograma
		//cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
		//cv::equalizeHist(src, dst);
		namedWindow("original", CV_WINDOW_AUTOSIZE); //creamos una ventana
		imshow("original", imageen);

		namedWindow("ecualizada", CV_WINDOW_AUTOSIZE); //creamos una ventana
		imshow("ecualizada", salida);



		// mostrar la imagen original y ecualizada


		/*
		int pixel_size = 8;

		namedWindow("Pixelate Effect", WINDOW_AUTOSIZE);
		createTrackbar("Pixel Size", "Pixelate Effect", &pixel_size, 50, ontrack, &imageen);
		ontrack(pixel_size, &imageen);
		*/
	}
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {


		Mat src = image;

		Mat src2 = image;

		cv::cvtColor(src, src, CV_LOAD_IMAGE_GRAYSCALE);
		Mat dst, dst2;
		Mat kernel = (Mat_<char>(3, 3) << 0, 1, 0,
			1, -4, 1,
			0, 1, 0);

		cv::filter2D(src, dst, src.depth(), kernel);
		namedWindow("borde1", CV_WINDOW_AUTOSIZE); //creamos una ventana
		imshow("borde1", dst);

		Mat kernel2 = (Mat_<char>(3, 3) << -2, -1, 0,
			-1, 1, 1,
			0, 1, 2);

		cv::filter2D(src2, dst2, src2.depth(), kernel2);
		namedWindow("borde2", CV_WINDOW_AUTOSIZE); //creamos una ventana
		imshow("borde2", dst2);

	}
			 

	private: System::Void button8_Click(System::Object^  sender, System::EventArgs^  e) {


	}
	private: System::Void trackBar1_Scroll(System::Object^  sender, System::EventArgs^  e) {

		Mat image2 = image;
		Mat salida;
		//cout << trackBar1->Value;
		Mat element = getStructuringElement(MORPH_CROSS,
			cv::Size(2 * trackBar1->Value + 1, 2 * trackBar1->Value + 1),
			cv::Point(trackBar1->Value, trackBar1->Value));

		erode(image2, salida, element);
		namedWindow("erode", CV_WINDOW_AUTOSIZE); //creamos una ventana
		imshow("erode", salida);

	}
private: System::Void trackBar2_Scroll(System::Object^  sender, System::EventArgs^  e) {
		Mat image2 = image;

		Mat salida;
		//cout << trackBar1->Value;
	
		Mat element = getStructuringElement(MORPH_ELLIPSE,
			cv::Size(2 * trackBar2->Value + 1, 2 * trackBar2->Value + 1),
			cv::Point(trackBar2->Value, trackBar2->Value));

		dilate(image2, salida, element);
		namedWindow("dilate", CV_WINDOW_AUTOSIZE); //creamos una ventana
		imshow("dilate", salida);
}
};
}
