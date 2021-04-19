#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

const char *const PatchFileName = "HACKASS.COM";
const long PatchOffset = 10;
char PatchBuf[1]{};

const float WindowWidth = 1280;
const float WindowHeight = 720;

const float ResistorWidth = 100;
const float ResistorHeight = 20;

const float ResistorHorizontalOffset = WindowWidth / 12;

const unsigned TitleTextCharacterSize = 25;
const unsigned BaseTextCharacterSize = 20;

const float TitleTextYOffset =  WindowHeight / 10;

const float CorrectAnswer = 48;

sf::Text setupResistorText(float x0, float y0, unsigned num, unsigned val, const sf::Font &font);
sf::RectangleShape setupResistorBox(float x0, float y0);
void setupWindowStartEventLoop(sf::RenderWindow *window, const sf::Font &textFont);
void patch();

signed main()
{
    sf::RenderWindow window{sf::VideoMode((unsigned) WindowWidth, (unsigned) WindowHeight), "crack"};

    sf::Music music;
    if (!music.openFromFile("music.wav")) {
        return EXIT_FAILURE;
    }
    music.play();
    music.setLoop(true);

    sf::Font textFont;
    if (!textFont.loadFromFile("arial.ttf")) {
        return EXIT_FAILURE;
    }

    setupWindowStartEventLoop(&window, textFont);

    return EXIT_SUCCESS;
}

void setupWindowStartEventLoop(sf::RenderWindow *window, const sf::Font &textFont)
{
    sf::Text text{{"To crack HACKASS.COM find the equivalent resistance of the circuit below and enter it:"},
                  textFont, TitleTextCharacterSize};
    sf::FloatRect rect = text.getLocalBounds();
    text.setOrigin(rect.left + rect.width / 2,
                   rect.top + rect.height / 2);
    text.setPosition(WindowWidth / 2, TitleTextCharacterSize / 2.f + TitleTextYOffset);

    sf::Vertex wires[] =
    {
    {{0,                   WindowHeight / 2}},
    {{WindowWidth / 3,     WindowHeight / 2}},

    {{WindowWidth / 3,     WindowHeight / 3}},
    {{WindowWidth / 3,     2 * WindowHeight / 3}},

    {{WindowWidth / 3,     WindowHeight / 3}},
    {{2 * WindowWidth / 3, WindowHeight / 3}},

    {{WindowWidth / 2,     WindowHeight / 3}},
    {{WindowWidth / 2,     2 * WindowHeight / 3}},

    {{WindowWidth / 3,     2 * WindowHeight / 3}},
    {{2 * WindowWidth / 3, 2 * WindowHeight / 3}},

    {{2 * WindowWidth / 3, WindowHeight / 3}},
    {{2 * WindowWidth / 3, 2 * WindowHeight / 3}},

    {{2 * WindowWidth / 3, WindowHeight / 2}},
    {{WindowWidth,         WindowHeight / 2}}
    };

    sf::Text r1Text = setupResistorText(WindowWidth / 3 + ResistorHorizontalOffset,
                                        WindowHeight / 3 - ResistorHeight / 2 - BaseTextCharacterSize / 2.f,
                                        1,
                                        15,
                                        textFont);
    sf::RectangleShape r1 = setupResistorBox(WindowWidth / 3 + ResistorHorizontalOffset,
                                             WindowHeight / 3);

    sf::Text r2Text = setupResistorText(2 * WindowWidth / 3 - ResistorHorizontalOffset,
                                        WindowHeight / 3 - ResistorHeight / 2 - BaseTextCharacterSize / 2.f,
                                        2,
                                        45,
                                        textFont);
    sf::RectangleShape r2 = setupResistorBox(2 * WindowWidth / 3 - ResistorHorizontalOffset,
                                             WindowHeight / 3);

    sf::Text r3Text = setupResistorText(WindowWidth / 3 + ResistorHorizontalOffset,
                                        2 * WindowHeight / 3 + ResistorHeight / 2 + BaseTextCharacterSize / 2.f,
                                        3,
                                        20,
                                        textFont);
    sf::RectangleShape r3 = setupResistorBox(WindowWidth / 3 + ResistorHorizontalOffset,
                                             2 * WindowHeight / 3);

    sf::Text r4Text = setupResistorText(2 * WindowWidth / 3 - ResistorHorizontalOffset,
                                        2 * WindowHeight / 3 + ResistorHeight / 2 + BaseTextCharacterSize / 2.f,
                                        4,
                                        60,
                                        textFont);
    sf::RectangleShape r4 = setupResistorBox(2 * WindowWidth / 3 - ResistorHorizontalOffset,
                                             2 * WindowHeight / 3);

    sf::Text r5Text = setupResistorText(WindowWidth / 2 + ResistorWidth / 2 + BaseTextCharacterSize / 2.f,
                                        WindowHeight / 2,
                                        5,
                                        66666,
                                        textFont);
    r5Text.rotate(90);
    sf::RectangleShape r5 = setupResistorBox(WindowWidth / 2,
                                             WindowHeight / 2);
    r5.rotate(90);

    sf::String input;
    sf::Text inputText{{""}, textFont, BaseTextCharacterSize};
    rect = inputText.getLocalBounds();
    inputText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
    inputText.setPosition(WindowWidth / 2, 3.f * TitleTextCharacterSize / 2 + TitleTextYOffset);

    float answer = 0;

    while (window->isOpen()) {
        sf::Event event{};
        while (window->pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::TextEntered:
                    switch (event.text.unicode) {
                        case '\u0008':
                            input = input.substring(0, input.getSize() - 1);
                            break;
                        default:
                            input += event.text.unicode;
                            break;
                    }
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Enter:
                            answer = std::stof(input.toWideString(), nullptr);
                            if (answer == CorrectAnswer) {
                                window->close();

                                patch();
                            }

                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }

            inputText.setString(input);
        }

        window->clear();
        window->draw(text);
        window->draw(inputText);
        window->draw(wires, sizeof(wires) / sizeof(*wires), sf::Lines);
        window->draw(r1Text);
        window->draw(r1);
        window->draw(r2Text);
        window->draw(r2);
        window->draw(r3Text);
        window->draw(r3);
        window->draw(r4Text);
        window->draw(r4);
        window->draw(r5Text);
        window->draw(r5);
        window->display();
    }
}

sf::Text setupResistorText(float x0, float y0, unsigned num, unsigned val, const sf::Font &font)
{
    static const char *const fmt = "R%u = %u Om";

    size_t textLen = std::snprintf(nullptr, 0, fmt, num, val);
    auto textBuf = (char *) std::calloc(textLen + 1, sizeof(char));
    std::snprintf(textBuf, textLen + 1, "R%u = %u Om", num, val);

    sf::Text graphicalText{{textBuf}, font};
    sf::Rect<float> rect = graphicalText.getLocalBounds();
    graphicalText.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
    graphicalText.setPosition(x0, y0);

    std::free(textBuf);

    return graphicalText;
}

sf::RectangleShape setupResistorBox(float x0, float y0)
{
    sf::RectangleShape box{{ResistorWidth, ResistorHeight}};
    sf::Rect<float> rect = box.getLocalBounds();
    box.setOrigin(rect.left + rect.width / 2, rect.top + rect.height / 2);
    box.setPosition(x0, y0);

    return box;
}

void patch()
{
    std::FILE *patchFile = std::fopen(PatchFileName, "r+b");

    std::fseek(patchFile, PatchOffset, SEEK_SET);
    std::fwrite(PatchBuf, sizeof(*PatchBuf), sizeof(PatchBuf) / sizeof(*PatchBuf), patchFile);

    std::fclose(patchFile);
}
