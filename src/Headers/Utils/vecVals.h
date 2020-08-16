namespace BGL {
    namespace Color {
        vec4f RED(1.0f, 0.0f, 0.0f, 1.0f);
        vec4f BLUE(0.0f, 0.0f, 1.0f, 1.0f);
        vec4f BLACK(0.0f, 0.0f, 0.0f, 1.0f);
        vec4f WHITE(1.0f, 1.0f, 1.0f, 1.0f);
        vec4f ORANGE(1.0f, 0.6f, 0.0f, 1.0f);
        vec4f GREEN(0.0f, 1.0f, 0.0f, 1.0f);
        vec4f YELLOW(1.0f, 1.0f, 0.0f, 1.0f);
        vec4f VIOLET(1.0f, 1.0f, 1.0f, 1.0f);
        vec4f PURPLE(0.5f, 0.0f, 0.5f, 1.0f);
        vec4f PINK(1.0f, 0.75f, 1.0f, 1.0f);
        vec4f GREY(0.5f, 0.5f, 0.5f, 1.0f);
        vec4f INDIGO(0.29f, 0.0f, 0.5f, 1.0f);
        vec4f BROWN(0.64f, 0.16f, 0.16f, 1.0f);
        vec4f NOCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
    }
    vec4f ColArray[] = {
       Color::RED,
       Color::BLUE,
       Color::ORANGE,
       Color::GREEN,
       Color::YELLOW,
       Color::VIOLET,
       Color::PURPLE,
       Color::PINK,
       Color::GREY,
       Color::INDIGO,
    };
    unsigned int ColSize = 10;
    vec4f randColor() {
        return ColArray[rand(0, ColSize - 1)];
    }
};

