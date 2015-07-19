
class native_screen;


class screen {
private:
	unsigned width, height;
	native_screen nscreen;
public:
	screen();
	screen(unsigned width, unsigned height);
	screen(const screen&);
	~screen();
	void set(unsigned width, unsigned height);
	unsigned getwidth();
	unsigned getheight();
	void setfocus();
};