#include "RealityGameEngine.h"
#include <fstream>
#include <strstream>
#include <algorithm>
using namespace std;

/*
It has nice errors with compliers but I want to upload here anyway since it was first thing I write myself instead of you knew copy from github like lazy person I am
I will improve it later on, I think: This is my hello world of graphic programming. to be honest I did not knew graphic programming was thing and all I want was make my own game.
I am huge fan of DirectX but that mostly nostalgia then anything else. You knew that I use to read article about DirectX when I was teenager and now I insteadly think DirectX
when I hear 3d graphic, but this program I writew was result of I followed tutorial of One lone coder Javidx9 (legend to me)
and sorry for ruining your code, I am truely sorry for that.

it was fun, so I will contine this appoch instead of just copy code from github with "Ctrl+C" and "Ctrl=V". I will try lto type the code myself, most of the time
sometime I might copy code from what I write since that what PardCode often do.

I will also keep developing my main game engine "Reality Engine DirectX12 (It will get update with new version when DirectX13 released, I think) but not stealong code or
ask from AI, most of the time. I need grow my skill as programmer order to render my 3d models I made.

And no, I do not own any codes written here. I can tell all these belomng to "Javidx9" since all I diod was change variable name so I can remember what they do later on
I have memory problom and no I am not talking about memory leaking in my progrma I foten cost but I often forget thing thanks to Corana the virus with too cute name that
almost killed one time
*/


//this is Vertex 3d that represents x, y, z of single vertex of mesh
struct Vectex3D
{
	float x, y, z;
};

//This is three group of vertex grouped as Triangle o we can form 3d flat surface
struct Triangle
{
	Vectex3D p[3];

	wchar_t sym;
	short col;
};

//Mesh will be group of triangles becuase triangles are simplest shape.
struct Mesh
{
	vector<Triangle> tris;

	bool LoadObj(string sFileName)
	{
		ifstream file(sFileName);
		if (!file.is_open())
			return false;

		//local catcha vertices
		vector<Vectex3D> vertices;

		//Now we will load data from file but we don't want read if there is no data left
		while (!file.eof())
		{
			//I am not sure how much my Marta file has, yet
			char line[25000];
			file.getline(line, 25000);

			strstream s;
			s << line;

			char junk;
			 //if it start with v then it is vertices
			if (line[0] == "v")
			{
				Vectex3D ver;
				s >> junk >> ver.x >> ver.y >> ver.z;
				vertices.push_back(ver);
			}

			//if it start with f mean face or triangle in this case
			if (line[0] == "f")
				//and both says it needs to be const char but that will break get line. I tested that.
			{
				Vectex3D tria;
				s >> junk >> tria.x >> tria.y >> tria.z;
				Triangle.push_back({ vertices[tria[0] - 1], vertices[tria[1] - 1], verticestria[2] - 1] });
			}
		}
		//I never used 'while" before. feel weird now

		return true;
	}
};

//Matrix is projection matris that project our 3d graphic in 2d screen
struct Matrix4x4
{
	float m[4][4] = { 0 };
};

class reality3DEngine : public  RealityGameEngine
{
public:
	reality3DEngine()
	{
		m_sAppName = L"Reality 3D Game Engine version 1.0";
	}

	virtual bool OnUserCreate() override
	{
		////All the vertex are group as three to make trianle here the it will form cub in the end
		//meshCube.tris = {
		//	//south side of cube that has two triangle and each line has three vector3d that created 2 traingle
		//	{ 0.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 0.0f },
		//	{ 0.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f },
		//	// East side of cube and these 1.0f and 0.0f floats are locations
		//	{ 1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f },
		//	{ 1.0f, 0.0f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 1.0f },
		//	// North side, all these data is simple cube
		//	{ 1.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f },
		//	{ 1.0f, 0.0f, 1.0f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f },
		//	//West side of cube
		//	{ 0.0f, 0.0f, 1.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 1.0f },
		//	{ 0.0f, 0.0f, 1.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, 0.0f },
		//	//Top side of cube
		//	{ 0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f },
		//	{ 0.0f, 1.0f, 0.0f,  1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 0.0f },
		//	//Buttom side of cube
		//	{ 1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f },
		//	{ 1.0f, 0.0f, 1.0f,  0.0f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f },
		//	//Each side has two tiangle and we have 6 side of cube here. cool
		//};

		//Load Marta obj here instead of cube
		meshCube.LoadObj("Marta_Summoner.obj");

		// Projection Matrix
		float fNear = 0.1f;
		float fFar = 1000.0f;
		float fFov = 90.0f;
		float fAspectRatio = (float)ScreenHeight() / (float)ScreenWidth();
		float fFovRad = 1.0f / tanf(fFov * 0.0f / 180.0f * 3.14159);

		matProj.m[0][0] = fAspectRatio * fFovRad;
		matProj.m[1][1] = fFovRad;
		matProj.m[2][2] = fFar / (fFar - fNear);
		matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
		matProj.m[2][3] = 1.0f;
		matProj.m[3][3] = 0.0f;

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) override
	{
		Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, FG_BLACK);

		//This will rotate our cube
		Matrix4x4 rotationZ, rotationX;
		float fTheta;
		fTheta += 1.0f * fElapsedTime;

		//Rotation X
		rotationZ.m[0][0] = cosf(fTheta * 0.5f);
		rotationZ.m[0][1] = sinf(fTheta * 0.5f);
		rotationZ.m[1][0] = -sinf(fTheta * 0.5f);
		rotationZ.m[1][1] = cosf(fTheta * 0.5f);
		rotationZ.m[2][2] = 1;
		rotationZ.m[3][3] = 1;

		//Rotation X
		rotationX.m[0][0] = 1;
		rotationX.m[1][1] = cosf(fTheta * 0.5f);
		rotationX.m[1][2] = sinf(fTheta * 0.5f);
		rotationX.m[2][1] = -sinf(fTheta * 0.5f);
		rotationX.m[2][2] = cosf(fTheta * 0.5f);
		rotationX.m[3][3] = 1;

		vector<Triangle> vecTriangleToRoaster;

		//for auto loop for draw traingle
		for (auto trio: meshCube.tris)
		{
			//Now we will darw our triangle with matrix we just created
			Triangle triProjected, TriTranslated, triRotetedZ, triRotatedZX;

			//now rotate cube here, order is important rotaion has to before translation to Matrix so buce rotate in it's oragin
			MultiplayMatrixVector(trio.p[0], triRotetedZ.p[0], rotationZ);
			MultiplayMatrixVector(trio.p[1], triRotetedZ.p[1], rotationZ);
			MultiplayMatrixVector(trio.p[2], triRotetedZ.p[2], rotationZ);

			//Second yhing is rotate X axis
			MultiplayMatrixVector(triRotetedZ.p[0], triRotatedZX.p[0], rotationX);
			MultiplayMatrixVector(triRotetedZ.p[1], triRotatedZX.p[1], rotationX);
			MultiplayMatrixVector(triRotetedZ.p[2], triRotatedZX.p[2], rotationX);

			//We going to apply world location to our cube wirh triTranslated so we can display cub front of us
			TriTranslated = triRotatedZX;
			TriTranslated.p[0].z = triRotatedZX.p[0].z + 21.0f;
			TriTranslated.p[1].z = triRotatedZX.p[1].z + 21.0f;
			TriTranslated.p[2].z = triRotatedZX.p[2].z + 21.0f;

			//Lines for normal map of mesh
			Vectex3D Normal, Line1, Line2;
			Line1.x = TriTranslated.p[1].x - TriTranslated.p[0].x;
			Line1.y = TriTranslated.p[1].y - TriTranslated.p[0].y;
			Line1.z = TriTranslated.p[1].z - TriTranslated.p[0].z;

			Line2.x = TriTranslated.p[2].x - TriTranslated.p[0].x;
			Line2.y = TriTranslated.p[2].y - TriTranslated.p[0].y;
			Line2.z = TriTranslated.p[2].z - TriTranslated.p[0].z;

			//Normal is cross product of these two line. Cross product is third line, Z line that calculate normal of surface of 3d
			Normal.x = Line1.y * Line2.z - Line1.z * Line2.y;
			Normal.y = Line1.z * Line2.x - Line1.x * Line2.z;
			Normal.z = Line1.z * Line2.y - Line1.y * Line2.x;

			//These will normalize the normal, I am not making these up it is just how it is.
			float normalizer = sqrt(Normal.x * Normal.x + Normal.y * Normal.y + Normal.z * Normal.z);
			Normal.x /= normalizer;
			Normal.y /= normalizer;
			Normal.z /= normalizer;

			//We only want to see if Z of normal is less then one AKA -1. Positive one mean it is otherside
			if (Normal.x * (TriTranslated.p[0].x - vCamera.x) + 
				Normal.y * (TriTranslated.p[0].y - vCamera.y) +
				Normal.z * (TriTranslated.p[0].z - vCamera.z) < 0.0f)
			{
				//The simple light, single direction light
				Vectex3D light_direction = { 0.0, 0.0, -1.0f };
				float light_ray = sqrt(light_direction.x * light_direction.x + light_direction.y * light_direction.y + light_direction.z * light_direction.z);
				light_direction.x /= light_ray;
				light_direction.y /= light_ray;
				light_direction.z /= light_ray;

				//now we have light data we can use dot product to check similiarities of these two
				float dotProduct = Normal.x * light_direction.x + Normal.y * light_direction.y + Normal.z * light_direction.z;

				CHAR_INFO c = GetColour(dotProduct);
				TriTranslated.col = c.Attributes;
				TriTranslated.sym = c.Char.UnicodeChar;

				//Time to us Multification Matrix. We will use our orginal TriTranslated as input and triProjecrted as outout. nice and easy tp remember
				//In other word translate 3d to 2d screen
				MultiplayMatrixVector(TriTranslated.p[0], triProjected.p[0], matProj);
				MultiplayMatrixVector(TriTranslated.p[1], triProjected.p[1], matProj);
				MultiplayMatrixVector(TriTranslated.p[2], triProjected.p[2], matProj);

				//transform color data from TriTranslated to triProjected
				triProjected.col = TriTranslated.col;
				triProjected.sym = TriTranslated.sym;

				//Scale into view for all three point
				triProjected.p[0].x += 1.0f;
				triProjected.p[0].y += 1.0f;

				triProjected.p[1].x += 1.0f;
				triProjected.p[1].y += 1.0f;

				triProjected.p[2].x += 1.0f;
				triProjected.p[2].y += 1.0f;

				//Now multiplay with half of screensize
				triProjected.p[0].x *= 0.5f * (float)ScreenWidth();
				triProjected.p[0].y *= 0.5f * (float)ScreenHeight();

				triProjected.p[1].x *= 0.5f * (float)ScreenWidth();
				triProjected.p[1].y *= 0.5f * (float)ScreenHeight();

				triProjected.p[2].x *= 0.5f * (float)ScreenWidth();
				triProjected.p[2].y *= 0.5f * (float)ScreenHeight();

				//getting triangle value for sorting
				vecTriangleToRoaster.push_back(triProjected);

			}
		}

		//sprting triangles
		sort(vecTriangleToRoaster.begin(), vecTriangleToRoaster.end(), [](Triangle t1, Triangle t2) {
			float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
			float z2 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
			return z1 > z2;
			});

		//I have no idea what I did wrong but it has nice red line
		for (auto& triProjected, verTriangleToRiaster)
		{
			//There was DrawTriangle but now it is FillTriangle. But DrawTriangle is for debugging. remember that, Mr idiot
			FillTriangle
			(
				triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y,
				triProjected.sym, triProjected.col);

			//You knew what let's draw all the wireframe on top of our mesh. I like that
			FillTriangle
			(
				triProjected.p[0].x, triProjected.p[0].y,
				triProjected.p[1].x, triProjected.p[1].y,
				triProjected.p[2].x, triProjected.p[2].y,
				PIXEL_SOLID, FG_RED);
			//so no I can't render my waifu here, sad face
		}

		return true;
	}


	int main()
	{
		reality3DEngine engine;
		if (engine.ConstructConsole(256, 256, 4, 4))
			engine.Start();

		return 0;
	}

private:
	//cube mesh
	Mesh meshCube;
	//projection matrix
	Matrix4x4 matProj;
	//Camera location Vecter
	Vectex3D vCamera;

	//Matrix multification void that we will use it lot
	void MultiplayMatrixVector(Vectex3D& input, Vectex3D output, Matrix4x4 matrix)
	{
		//I name thing that easy to read and remember later on, why because I have memory problem
		output.x = input.x * matrix.m[0][0] + input.y * matrix.m[1][0] + input.z * matrix.m[2][0] + matrix.m[3][0];
		output.y = input.x * matrix.m[0][1] + input.y * matrix.m[1][1] + input.z * matrix.m[2][1] + matrix.m[3][1];
		output.z = input.x * matrix.m[0][2] + input.y * matrix.m[1][2] + input.z * matrix.m[2][2] + matrix.m[3][2];
		float w = input.x * matrix.m[0][3] + input.y * matrix.m[1][3] + input.z * matrix.m[2][3] + matrix.m[3][3];

		//since we dealing with 4d not 3d we devide with w but we will do that unless w is not equels to 0
		if (w != 0.0f)
		{
			output.x /= w;
			output.y /= w;
			output.z /= w;
		}
	}

	//This function is for colouring stuff
	CHAR_INFO GetColour(float lum)
	{
		short bg_col, fg_col;
		wchar_t sym;
		int pixel_bw = (int)(13.0 * lum);

		switch (pixel_bw)
		{
		case 0: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_SOLID;
			break;
		case 1: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_QUARTER;
			break;
		case 2: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_HALF;
			break;
		case 3: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_THREEQUARTERS;
			break;

		case 4: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_SOLID;
			break;
		case 5: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_QUARTER;
			break;
		case 6: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_HALF;
			break;
		case 7: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_THREEQUARTERS;
			break;

		case 8: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_SOLID;
			break;
		case 9: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_QUARTER;
			break;
		case 10: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_HALF;
			break;
		case 11: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_THREEQUARTERS;
			break;
		case 12: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_SOLID;
			break;

		default: bg_col = BG_DARK_GREY; fg_col = FG_BLUE; sym = PIXEL_SOLID;
			break;
		}
	}
};