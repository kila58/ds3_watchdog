#pragma once

class Detection
{
private:
	DWORD_PTR base_a;
	DWORD_PTR base_b;
	DWORD_PTR xb;
	DWORD_PTR xc;

public:
	bool Init();
	void Frame(D3D11Renderer* renderer);
};

extern Detection detection;