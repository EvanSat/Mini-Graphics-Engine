/*
*	Mini Graphics Engine
*
*	@author: Evan Sabado
*/

#include <iostream>
#include <fstream>
#include <glut.h>
#include <string>	// Used to convert string into double using 'stoi'
#include <conio.h>	// Allows for keyboard inputs into the console
#include <cmath>


const double windowSizeX = 1200;
const double windowSizeY = 720;
const int arrayColumns = 3;
const int arrayRows = 62;

double worldCordsX[] = { -2000, 2000 };
double worldCordsY[] = { -2000, 2000 };
double worldCordsZ[] = { -2000, 2000 };

//Used for angle rotation using glRotated
double angleX = 0;
double angleY = 0;
double angleZ = 0;
//double angle = 0;		This was supposed to help change the rotation translations for each axis, did not work as intended

std::string pixaArray[arrayRows][arrayColumns];


//handles matrices calculation for each tranlation matrix
void translationCalculation(double inputMatrix[][4]) {

	double tempValue = 0;

	for (int a = 0; a < arrayRows; a++) {		// handles every row in testArray
		if (pixaArray[a][0] == "J") {			// Checks to see if this row includes a J
			a += 1;
		}
		for (int b = 0; b < 3; b++) {			// handles every column in testArray && every row in translationMatrix
			for (int d = 0; d < 4; d++) {		// handles every column in translationMatrix
				if (d == 3) {
					std::cout << pixaArray[a][b] << " is added by " << inputMatrix[b][d] << std::endl;
					tempValue += inputMatrix[b][d];
				}
				else {
					std::cout << pixaArray[a][b] << " is multiplied by " << inputMatrix[b][d] << std::endl;
					tempValue += (stod(pixaArray[a][b])) * inputMatrix[b][d];
				}
			}
			pixaArray[a][b] = std::to_string(tempValue);
			tempValue = 0;
		}
	}
}


void xPositionTranlationRight() {
	double rightTranslation[4][4] =	{ {1, 0, 0, 20},
									  {0, 1, 0, 0},
									  {0, 0, 1, 0}, 
									  {0, 0, 0, 0} };

	translationCalculation(rightTranslation);
}


void xPositionTranlationLeft() {
	double leftTranslation[4][4] = { {1, 0, 0, -20},
									 {0, 1, 0, 0},
									 {0, 0, 1, 0},
									 {0, 0, 0, 0} };

	translationCalculation(leftTranslation);
}


void yPositionTranslationUp() {
	double upTranslation[4][4] = { {1, 0, 0, 0},
								   {0, 1, 0, 20},
								   {0, 0, 1, 0},
								   {0, 0, 0, 0} };

	translationCalculation(upTranslation);
}


void yPositionTranslationDown() {
	double downTranslation[4][4] = { {1, 0, 0, 0},
									 {0, 1, 0, -20},
									 {0, 0, 1, 0},
									 {0, 0, 0, 0} };

	translationCalculation(downTranslation);
}


void zPositionTranslationIn() {
	double inTranslation[4][4] = { {1, 0, 0, 0},
								   {0, 1, 0, 0},
							  	   {0, 0, 1, 20},
								   {0, 0, 0, 0} };

	translationCalculation(inTranslation);
}


void zPositionTranslationOut() {
	double outTranslation[4][4] = { {1, 0, 0, 0},
								    {0, 1, 0, 0},
								    {0, 0, 1, -20},
								    {0, 0, 0, 0} };

	translationCalculation(outTranslation);
}

double convertDegreesToRadian(double degrees) {
	double pi = 3.14159265;				// An approximation of PI will work
	return(degrees * (pi / 180));
}


void xAxisRotation() {
	//angle += 5;
	//if (angle > 360.0) {
	//	angle -= 360.0;
	//}
	//double xAxisTranslation[4][4] = { {1, 0         , 0          , 0},
	//								    {0, cos(angle), -sin(angle), 0},
	//								    {0, sin(angle), cos(angle) , 0},
	//								    {0, 0         , 0          , 0} };

	//translationCalculation(xAxisTranslation);

	angleX += 5;
}


void yAxisRotation() {
	//angle += 5;
	//if (angle > 360.0) {
	//	angle -= 360.0;
	//}
	//double yAxisTranslation[4][4] = { {cos(angle), 0, sin(angle), 0},
	//								    {0          , 1, 0         , 0},
	//								    {-sin(angle), 0, cos(angle), 0},
	//								    {0          , 0, 0         , 0} };

	//translationCalculation(yAxisTranslation);

	angleY += 5;
}


void zAxisRotation() {
	//angle += 5;
	//if (angle > 360.0) {
	//	angle -= 360.0;
	//}
	//double yAxisTranslation[4][4] = { {cos(angle), -sin(angle), 0, 0},
	//									{sin(angle), cos(angle) , 0, 0},
	//									{0         , 0          , 0, 0},
	//									{0         , 0          , 0, 0} };

	//translationCalculation(yAxisTranslation);

	angleZ += 5;
}


void readFile() {
	std::ifstream file("pixa.dat");

	std::string tempString;

	if (file.is_open()) {
		for (int x = 0; x < arrayRows; x++) {
			for (int y = 0; y < arrayColumns; y++) {
				file >> tempString;
				if (tempString == "J") {
					pixaArray[x][y] = tempString;
					std::cout << pixaArray[x][y] << std::endl;
					break;
				}
				else {
					pixaArray[x][y] = tempString;
					if (y == 2) {
						std::cout << pixaArray[x][y] << std::endl;
					}
					else {
						std::cout << pixaArray[x][y] << " ";
					}
				}
				tempString = " ";
			}
		}
	}
	file.close();
}


void resetPixaArray() {
	readFile();
	angleX = 0;
	angleY = 0;
	angleZ = 0;
}


void timerFunc(int) {
	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timerFunc, 0);

	char key = _getch();
	int asciiValue = key;

	switch (asciiValue) {
		case 76:
		case 108: {

			xPositionTranlationLeft();
			break;
		}
		case 82:
		case 114: {
			xPositionTranlationRight();
			break;
		}
		case 85:
		case 117: {
			yPositionTranslationUp();
			break;
		}
		case 68:
		case 100: {
			yPositionTranslationDown();
			break;
		}
		case 73:
		case 105: {
			zPositionTranslationIn();
			break;
		}
		case 79:
		case 111: {
			zPositionTranslationOut();
			break;
		}
		case 88:
		case 120: {
			xAxisRotation();
			break;
		}
		case 89:
		case 121: {
			yAxisRotation();
			break;
		}
		case 90:
		case 122: {
			zAxisRotation();
			break;
		}
		case 49:{
			resetPixaArray();
			break;
		}
		case 27:
		case 81:
		case 113: {
			exit(0);
		}
	}
}


void drawLines() {

	const double conversionRatioX = (windowSizeX - 1) / (abs(worldCordsX[0]) + worldCordsX[1]);	
	const double conversionRatioY = (windowSizeY - 1) / (abs(worldCordsY[0]) + worldCordsY[1]);
	const double conversionRatioZ = (windowSizeX - 1) / (abs(worldCordsX[0]) + worldCordsX[1]);	// made the Z axis mirror the X axis conversion to negate distortion

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glColor3ub(255, 200, 0);
	glRotated(angleX, 1, 0, 0);	
	glRotated(angleY, 0, 1, 0);
	glRotated(angleZ, 0, 0, 1);

	double xPos = 0, yPos = 0, zPos = 0;

	for (int i = 0; i < arrayRows; i++) {
		for (int j = 0; j < arrayColumns; j++) {
			if (pixaArray[i][j] == "J") {
				glEnd();
				glBegin(GL_LINE_LOOP);
				std::cout << std::endl;
				break;
			}
			else switch (j) {
			case 0:							// handles X position
				xPos = (stod(pixaArray[i][j])) * conversionRatioX;				
				break;
			case 1:							// handles Y position
				yPos = (stod(pixaArray[i][j])) * conversionRatioY;				
				break;
			case 2:							// handles Z position
				zPos = (stod(pixaArray[i][j])) * conversionRatioZ;
				break;
			}
		}
		if (pixaArray[i][0] != "J") {
			glVertex3d(xPos, yPos, zPos);
			std::cout << "Vertex X:" << xPos << " Y:" << yPos << " Z:" << zPos << std::endl;
		}
	}
	glEnd();
	glutSwapBuffers();
}


void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(windowSizeX * -1, windowSizeX, windowSizeY * -1, windowSizeY, -2000.0, 2000.0);
	glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 

	readFile();

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(windowSizeX, windowSizeY);
	glutCreateWindow("SabadoEvan_MP4");

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutDisplayFunc(drawLines);
	glutReshapeFunc(reshape);

	glutTimerFunc(1000, timerFunc, 0);

	glutMainLoop();

	return 0;
}


