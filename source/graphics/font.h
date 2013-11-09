#ifndef FONT
#define FONT

#include <string>
#include <map>

class Font;

typedef std::map<std::string, Font* > FontMap;
typedef std::pair<std::string, Font* > FontPair;

class Font
{
public:

    static Font * GetFont(const char * filename, int size);
    static void DestroyFonts();
	~Font();

	void * font;
private:
	Font(void* font);

	static FontMap fonts;
};

#endif

