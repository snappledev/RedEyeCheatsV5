#pragma once
class color
{
public:
	color() {
		*((int*)this) = 0;
	}
	color(int r, int g, int b) {
		Setcolor(r, g, b, 255);
	}
	color(int r, int g, int b, int a) {
		Setcolor(r, g, b, a);
	}
	color(int a) {
		Setcolor(_color[0], _color[1], _color[2], a);
	}
	color(int* arr, int a) {
		Setcolor(arr[0], arr[1], arr[2], a);
	}
	color(int* arr) {
		Setcolor(arr[0], arr[1], arr[2], 255);
	}

	void Setcolor(int r, int g, int b, int a = 255) {
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)a;
	}

	void Getcolor(int& r, int& g, int& b, int& a) const {
		r = _color[0];
		g = _color[1];
		b = _color[2];
		a = _color[3];
	}

	void SetRawcolor(int color32) {
		*((int*)this) = color32;
	}

	int GetRawcolor() const {
		return *((int*)this);
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }
	inline float rBase() const { return _color[0] / 255.0f; }
	inline float gBase() const { return _color[1] / 255.0f; }
	inline float bBase() const { return _color[2] / 255.0f; }
	inline float aBase() const { return _color[3] / 255.0f; }
	void SetAlpha(int a) { _color[0] = (unsigned char)a; }
	int  GetAlpha() { return _color[0]; }
	unsigned char& operator[](int index) {
		return _color[index];
	}
	const unsigned char& operator[](int index) const {
		return _color[index];
	}
	bool operator == (const color& rhs) const {
		return (*((int*)this) == *((int*)& rhs));
	}
	bool operator != (const color & rhs) const {
		return !(operator==(rhs));
	}
	color& operator=(const color & rhs) {
		SetRawcolor(rhs.GetRawcolor());
		return *this;
	}
	float Hue() const {
		if (_color[0] == _color[1] && _color[1] == _color[2])
			return 0.0f;
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;
		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.0f;
		if (r == max)
			hue = (g - b) / delta;
		else if (g == max)
			hue = 2 + (b - r) / delta;
		else if (b == max)
			hue = 4 + (r - g) / delta;
		hue *= 60;
		if (hue < 0.0f)
			hue += 360.0f;
		return hue;
	}

	float Saturation() const {
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;
		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float l, s = 0;
		if (max != min) {
			l = (max + min) / 2;
			if (l <= 0.5f)
				s = (max - min) / (max + min);
			else
				s = (max - min) / (2 - max - min);
		}
		return s;
	}

	float Brightness() const {
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return (max + min) / 2;
	}

	static color FromHSB(float hue, float saturation, float brightness) {
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));
		if (h < 1)
			return color((unsigned char)(brightness * 255),(unsigned char)(t * 255),(unsigned char)(p * 255));
		else if (h < 2)
			return color((unsigned char)(q * 255),(unsigned char)(brightness * 255),(unsigned char)(p * 255));
		else if (h < 3)
			return color((unsigned char)(p * 255),(unsigned char)(brightness * 255),(unsigned char)(t * 255));
		else if (h < 4)
			return color((unsigned char)(p * 255),(unsigned char)(q * 255),(unsigned char)(brightness * 255));
		else if (h < 5)
			return color((unsigned char)(t * 255),(unsigned char)(p * 255),(unsigned char)(brightness * 255));
		else
			return color((unsigned char)(brightness * 255),(unsigned char)(p * 255),(unsigned char)(q * 255));
	}
private:
	unsigned char _color[4];
}; 