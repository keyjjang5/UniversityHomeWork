//windows � ���α׷�(.exe)
////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"

#include <fstream>
typedef struct
{
	float x, y, z;
}VertexType;

typedef struct
{
	int vIndex1, vIndex2, vIndex3;
	int tIndex1, tIndex2, tIndex3;
	int nIndex1, nIndex2, nIndex3;
}FaceType;

bool ReadFileCounts(char*, int&, int&, int&, int&);
//bool LoadDataStructures(char*, int, int, int, int, int&, int&, int);
bool LoadDataStructures(char*, int, int, int, int, int);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	SystemClass* System;
	bool result;
	int cntObj = 0;
	int cntPoly = 0;

//	char filename[19][256] = { "book.obj",
//"carpet.obj",
//"ceilinglight.obj",
//"circletable.obj",
//"cushion1.obj",
//"cushion2.obj",
//"cushion3.obj",
////"door.obj",
//"ground.obj",
//"picture.obj",
//"picturecase.obj",
//"sofa1.obj",
//"sofa2.obj",
//"table.obj",
//"tv.obj",
//"tvcase.obj",
//"tvwall.obj",
//"wall.obj", 
//"stair.obj",
//"stairwall.obj"
//	};
//	int vertexCount, textureCount, normalCount, faceCount;
//
//	for (int i = 0; i < 19; i++)
//	{
//		result = ReadFileCounts(filename[i], vertexCount, textureCount, normalCount, faceCount);
//		if (!result)
//		{
//			return -1;
//		}
//
//		result = LoadDataStructures(filename[i], vertexCount, textureCount, normalCount, faceCount, i);
//		if (!result)
//		{
//			return -1;
//		}
//	}


	// Create the system object.
	System = new SystemClass;
	if (!System)
	{
		return 0;
	}
	// Initialize and run the system object.
	result = System->Initialize(cntObj, cntPoly);
	if (result)
	{
		System->Run();
	}
	// Shutdown and release the system object.
	System->Shutdown();
	delete System;
	System = 0;
	return 0;
}

bool ReadFileCounts(char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount)
{
	ifstream fin;
	char input;


	// ī��Ʈ�� �ʱ�ȭ�մϴ�.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// ������ ���� ��.
	fin.open(filename);

	// ���� ���⿡ �����ߴ��� Ȯ���մϴ�.
	if (fin.fail() == true)
	{
		return false;
	}

	// ���Ͽ��� ���� ���� ������ ���� ���� �� ������ ��� �н��ϴ�.
	fin.get(input);
	while (!fin.eof())
	{
		// ������ 'v'�� �����ϸ� ������, �ؽ�ó ��ǥ �Ǵ� ���� ���͸� ����մϴ�.
		if (input == 'v')
		{
			fin.get(input);
			if (input == ' ') { vertexCount++; }
			if (input == 't') { textureCount++; }
			if (input == 'n') { normalCount++; }
		}

		// ������ 'f'�� �����ϸ�� ���� ������ŵ�ϴ�.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ') { faceCount++; }
		}

		// �׷��� ������ ������ ���� �н��ϴ�.
		while (input != '\n')
		{
			fin.get(input);
		}

		// ���� ���� ���� �κ��� �б� �����Ѵ�.
		fin.get(input);
	}

	// ������ �ݽ��ϴ�.
	fin.close();

	return true;
}


bool LoadDataStructures(char* filename, int vertexCount, int textureCount, int normalCount, int faceCount, int num)
{
	VertexType *vertices, *texcoords, *normals;
	FaceType *faces;
	ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;
	ofstream fout;


	// �� ���� ������ ������ �ʱ�ȭ�մϴ�.
	vertices = new VertexType[vertexCount];
	if (!vertices)
	{
		return false;
	}

	texcoords = new VertexType[textureCount];
	if (!texcoords)
	{
		return false;
	}

	normals = new VertexType[normalCount];
	if (!normals)
	{
		return false;
	}

	faces = new FaceType[faceCount];
	if (!faces)
	{
		return false;
	}

	// �ε����� �ʱ�ȭ�մϴ�.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// ������ ���� ��.
	fin.open(filename);

	// ���� ���⿡ �����ߴ��� Ȯ���Ͻʽÿ�.
	if (fin.fail() == true)
	{
		return false;
	}

	// ����, �ؽ�ó ��ǥ �� ������ ������ ������ �о���Դϴ�.
	// �߿� : Maya�� ������ ��ǥ�踦 ����ϱ� ������ �޼� ��ǥ��� ��ȯ�Ѵ�.
	fin.get(input);
	while (!fin.eof())
	{
		if (input == 'v')
		{
			fin.get(input);

			// ������ �н��ϴ�.
			if (input == ' ')
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				// Z ������ ������ �޼� �ý������� �ٲ۴�.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}

			// �ؽ�ó uv ��ǥ�� �н��ϴ�.
			if (input == 't')
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				// V �ؽ�ó ��ǥ�� �޼� �ý������� ������ŵ�ϴ�.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			// ������ �н��ϴ�.
			if (input == 'n')
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				// Z ������ �������� �޼� �ý������� �����մϴ�.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		// ǥ���� �д´�.
		if (input == 'f')
		{
			fin.get(input);
			if (input == ' ')
			{
				// ������ �ý��ۿ��� �޼� �ý������� ��ȯ�ϱ� ���� ǥ�� �����͸� �Ųٷ� �н��ϴ�.
				fin >> faces[faceIndex].vIndex3 >> input2 >> faces[faceIndex].tIndex3 >> input2 >> faces[faceIndex].nIndex3
					>> faces[faceIndex].vIndex2 >> input2 >> faces[faceIndex].tIndex2 >> input2 >> faces[faceIndex].nIndex2
					>> faces[faceIndex].vIndex1 >> input2 >> faces[faceIndex].tIndex1 >> input2 >> faces[faceIndex].nIndex1;
				faceIndex++;
			}
		}

		// ������ ���� �н��ϴ�.
		while (input != '\n')
		{
			fin.get(input);
			if (fin.eof()) break;
		}

		// ���� ���� ���� �κ��� �б� �����Ѵ�.
		fin.get(input);
	}

	// ������ �ݽ��ϴ�.
	fin.close();

	// ��� ������ ���ϴ�.
	switch (num)
	{
	case 0:
		fout.open("model0.txt");
		break;
	case 1:
		fout.open("model1.txt");
		break;
	case 2:
		fout.open("model2.txt");
		break;
	case 3:
		fout.open("model3.txt");
		break;
	case 4:
		fout.open("model4.txt");
		break;
	case 5:
		fout.open("model5.txt");
		break;
	case 6:
		fout.open("model6.txt");
		break;
	case 7:
		fout.open("model7.txt");
		break;
	case 8:
		fout.open("model8.txt");
		break;
	case 9:
		fout.open("model9.txt");
		break;
	case 10:
		fout.open("model10.txt");
		break;
	case 11:
		fout.open("model11.txt");
		break;
	case 12:
		fout.open("model12.txt");
		break;
	case 13:
		fout.open("model13.txt");
		break;
	case 14:
		fout.open("model14.txt");
		break;
	case 15:
		fout.open("model15.txt");
		break;
	case 16:
		fout.open("model16.txt");
		break;
	case 17:
		fout.open("model17.txt");
		break;
	case 18:
		fout.open("model18.txt");
		break;
	case 19:
		fout.open("model19.txt");
		break;
	default:
		break;
	}
	//fout.open(name);

	// �� ���Ŀ��� ����ϴ� ���� ����� �ۼ��մϴ�.
	fout << "Vertex Count: " << (faceCount * 3) << endl;
	fout << endl;
	fout << "Data:" << endl;
	fout << endl;

	// ���� ������ �ݺ��ϰ� ������ �� �������� ����մϴ�.
	for (int i = 0; i < faceIndex; i++)
	{
		vIndex = faces[i].vIndex1 - 1;
		tIndex = faces[i].tIndex1 - 1;
		nIndex = faces[i].nIndex1 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex2 - 1;
		tIndex = faces[i].tIndex2 - 1;
		nIndex = faces[i].nIndex2 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;

		vIndex = faces[i].vIndex3 - 1;
		tIndex = faces[i].tIndex3 - 1;
		nIndex = faces[i].nIndex3 - 1;

		fout << vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << endl;
	}

	// ��� ������ �ݴ´�.
	fout.close();

	// �� ���� ������ ������ �����Ѵ�.
	if (vertices)
	{
		delete[] vertices;
		vertices = 0;
	}
	if (texcoords)
	{
		delete[] texcoords;
		texcoords = 0;
	}
	if (normals)
	{
		delete[] normals;
		normals = 0;
	}
	if (faces)
	{
		delete[] faces;
		faces = 0;
	}

	return true;
}