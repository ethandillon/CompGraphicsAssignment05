#ifndef X11_H
#define X11_H


#include <GLFW/glfw3.h>
//#include <sstream>
//#include <iostream>
#include <memory>
#include <GLM/vec4.hpp>


namespace cs4722 {
    /**
     *  Class color stores a color as an RGBA quadruple of float values in the range from 0.0 to 1.0.
     */
	class Color {
	public:
		glm::vec4 colorVec;


		~Color() = default;


        /**
         * \brief Initialize the color using the RGBA values provided.
         *
         * @param r  Red component, in the range from 0.0 to 1.0
         * @param g   Green component, in the range from 0.0 to 1.0
         * @param b   Blue component, in the range from 0.0 to 1.0
         * @param a   Alpha component, in the range from 0.0 to 1.0
         */
        Color(double r, double g, double b, double a)
            : colorVec(r, g, b, a) {}

        /**
         * \brief Initialize the color to black with an alpha of 0.0.
         */
            Color() : Color(0.0, 0, 0, 0) {}


        /**
          * \brief Initialize the color using the RGBA values provided.
          *
          * @param r  Red component, in the range from 0 to 255, inclusive
          * @param g   Green component, in the range from 0 to 255, inclusive
          * @param b   Blue component, in the range from 0 to 255, inclusive
          * @param a   Alpha component, in the range from 0 to 255, inclusive
          */
        static Color colorRGBA(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte a)
//			: color(r/255.0, g/255.0, b/255.0, a/255.0)
        {
            return Color(r/255.0, g/255.0, b/255.0, a/255.0);
        }

        /**
       * \brief Initialize the color using the RGBA values provided.
       *  The alpha component is set to 255.
       *
       * @param r  Red component, in the range from 0 to 255, inclusive
       * @param g   Green component, in the range from 0 to 255, inclusive
       * @param b   Blue component, in the range from 0 to 255, inclusive
       */
        static Color colorRGB(const GLubyte r, const GLubyte g, const GLubyte b)
//			: color(r, g, b, 255)
		{
            return colorRGBA(r,g,b,255);
		}




//		color(const color& c) = default;

        /**
         * \brief Return the red component as an unsigned byte.
         */
        GLubyte r() {
            return (GLubyte)(colorVec.r * 255);
        }

        /**
         * \brief Return the green component as an unsigned byte.
         */
        GLubyte g() {
            return (GLubyte)(colorVec.g * 255);
        }

        /**
         * \brief Return the blue component as an unsigned byte.
         */
        GLubyte b() {
            return (GLubyte)(colorVec.b * 255);
        }

        /**
         * \brief Return the alpha component as an unsigned byte.
         */
        GLubyte a() {
            return (GLubyte)(colorVec.a * 255);
        }



        /**
         * \brief Return alpha times this color plus 1-alpha times the other color
         *
         * @param alpha  Mixing parameter, should be in the range from 0.0 to 1.0
         * @param other  The color to mix with this color
         * @return alpha times this color plus 1-alpha times the other color
         */
		Color mix(double alpha, const Color &other) {
            Color rtval(alpha * colorVec.r + (1- alpha) * other.colorVec.r,
                        alpha * colorVec.g + (1- alpha) * other.colorVec.g,
                        alpha * colorVec.b + (1- alpha) * other.colorVec.b,
                        alpha * colorVec.a + (1- alpha) * other.colorVec.a
                        );
//            rtval.r = (GLubyte)(alpha * r + (1-alpha) * other.r);
//            rtval.g = (GLubyte)(alpha * g + (1-alpha) * other.g);
//            rtval.b = (GLubyte)(alpha * b + (1-alpha) * other.b);
            return rtval;
        }

		Color& operator=(const Color& x) = default;


//		const glm::vec4* as_vec4() const
//        {
//            return &color_vec;
//        }
//        glm::vec4 as_vec4();

        /**
         * \brief Return a four tuple of floats that represents this color.
         *
         *  This function just returns a pointer to the float array stored by  glm::vec4 object.
         *  No memory is allocated for this operation.
         */
		const GLfloat* asFloatArray() const {
            return &colorVec.x;
        }

        /* *
         * \brief Return a four tuple of floats that represents this color.
         *      The float is packaged in a <code>unique_ptr</code> which will take
         *      care of deleting the allocated storage when no longer needed.
         *
         *  This function calls as_float_array(), wraps the array, and returns the unique_ptr.
         *
         */
//        std::unique_ptr<GLfloat[]> as_float_array() const;

        /* *
         * \brief This function converts a color from internal format to float in the same manner as
         *      <code>as_float_array</code>.
         *      The resulting values are put in the argument.
         *
         *  \warning  This function is <strong>dangerous</strong>.
         *      If an array with fewer than four elements is passed as the parameter
         *      <code>color</code> then this function will try to store values
         *      in the memory following the array.
         *      This leads to undefined behavior.
         *      If you are lucky, the program will crash during testing.
         *      If you are not so lucky, you will be reading in the news about how your program was hacked to
         *      allow access to the data for thousands of users.
         *
         *
         *   Why would we provide such a dangerous function?
         *   Because it supports higher performance.
         *   The other 'as_float_array' functions allocate arrays each time they are executed.
         *   Those arrays must be deleted.
         *   For material colors this will happen over and over as the scene is displayed.
         *   It is quicker to allocate the storage once, before the program starts running, and
         *   then just copy the appropriate values into place.
         *
         * @param color  An array of at least 4 elements.
         */
//        void as_float_array(GLfloat* color) const;


//		explicit operator std::string() const;

//		friend std::ostream& operator<<(std::ostream& output, const color& c);

//        color operator*(const color& y);


	};


	class X11 {
	public:
		static  Color alice_blue;
		static  Color antique_white;
		static  Color antique_white1;
		static  Color antique_white2;
		static  Color antique_white3;
		static  Color antique_white4;
		static  Color aquamarine;
		static  Color aquamarine1;
		static  Color aquamarine2;
		static  Color aquamarine3;
		static  Color aquamarine4;
		static  Color azure;
		static  Color azure1;
		static  Color azure2;
		static  Color azure3;
		static  Color azure4;
		static  Color beige;
		static  Color bisque;
		static  Color bisque1;
		static  Color bisque2;
		static  Color bisque3;
		static  Color bisque4;
		static  Color black;
		static  Color blanched_almond;
		static  Color blue;
		static  Color blue1;
		static  Color blue2;
		static  Color blue3;
		static  Color blue4;
		static  Color blue_violet;
		static  Color brown;
		static  Color brown1;
		static  Color brown2;
		static  Color brown3;
		static  Color brown4;
		static  Color burlywood;
		static  Color burlywood1;
		static  Color burlywood2;
		static  Color burlywood3;
		static  Color burlywood4;
		static  Color cadet_blue;
		static  Color cadet_blue1;
		static  Color cadet_blue2;
		static  Color cadet_blue3;
		static  Color cadet_blue4;
		static  Color chartreuse;
		static  Color chartreuse1;
		static  Color chartreuse2;
		static  Color chartreuse3;
		static  Color chartreuse4;
		static  Color chocolate;
		static  Color chocolate1;
		static  Color chocolate2;
		static  Color chocolate3;
		static  Color chocolate4;
		static  Color coral;
		static  Color coral1;
		static  Color coral2;
		static  Color coral3;
		static  Color coral4;
		static  Color cornflower_blue;
		static  Color cornsilk;
		static  Color cornsilk1;
		static  Color cornsilk2;
		static  Color cornsilk3;
		static  Color cornsilk4;
		static  Color cyan;
		static  Color cyan1;
		static  Color cyan2;
		static  Color cyan3;
		static  Color cyan4;
		static  Color dark_blue;
		static  Color dark_cyan;
		static  Color dark_goldenrod;
		static  Color dark_goldenrod1;
		static  Color dark_goldenrod2;
		static  Color dark_goldenrod3;
		static  Color dark_goldenrod4;
		static  Color dark_gray;
		static  Color dark_green;
		static  Color dark_grey;
		static  Color dark_khaki;
		static  Color dark_magenta;
		static  Color dark_olive_green;
		static  Color dark_olive_green1;
		static  Color dark_olive_green2;
		static  Color dark_olive_green3;
		static  Color dark_olive_green4;
		static  Color dark_orange;
		static  Color dark_orange1;
		static  Color dark_orange2;
		static  Color dark_orange3;
		static  Color dark_orange4;
		static  Color dark_orchid;
		static  Color dark_orchid1;
		static  Color dark_orchid2;
		static  Color dark_orchid3;
		static  Color dark_orchid4;
		static  Color dark_red;
		static  Color dark_salmon;
		static  Color dark_sea_green;
		static  Color dark_sea_green1;
		static  Color dark_sea_green2;
		static  Color dark_sea_green3;
		static  Color dark_sea_green4;
		static  Color dark_slate_blue;
		static  Color dark_slate_gray;
		static  Color dark_slate_gray1;
		static  Color dark_slate_gray2;
		static  Color dark_slate_gray3;
		static  Color dark_slate_gray4;
		static  Color dark_slate_grey;
		static  Color dark_turquoise;
		static  Color dark_violet;
		static  Color deep_pink;
		static  Color deep_pink1;
		static  Color deep_pink2;
		static  Color deep_pink3;
		static  Color deep_pink4;
		static  Color deep_sky_blue;
		static  Color deep_sky_blue1;
		static  Color deep_sky_blue2;
		static  Color deep_sky_blue3;
		static  Color deep_sky_blue4;
		static  Color dim_gray;
		static  Color dim_grey;
		static  Color dodger_blue;
		static  Color dodger_blue1;
		static  Color dodger_blue2;
		static  Color dodger_blue3;
		static  Color dodger_blue4;
		static  Color firebrick;
		static  Color firebrick1;
		static  Color firebrick2;
		static  Color firebrick3;
		static  Color firebrick4;
		static  Color floral_white;
		static  Color forest_green;
		static  Color gainsboro;
		static  Color ghost_white;
		static  Color gold;
		static  Color gold1;
		static  Color gold2;
		static  Color gold3;
		static  Color gold4;
		static  Color goldenrod;
		static  Color goldenrod1;
		static  Color goldenrod2;
		static  Color goldenrod3;
		static  Color goldenrod4;
		static  Color gray;
		static  Color gray0;
		static  Color gray1;
		static  Color gray10;
		static  Color gray100;
		static  Color gray11;
		static  Color gray12;
		static  Color gray13;
		static  Color gray14;
		static  Color gray15;
		static  Color gray16;
		static  Color gray17;
		static  Color gray18;
		static  Color gray19;
		static  Color gray2;
		static  Color gray20;
		static  Color gray21;
		static  Color gray22;
		static  Color gray23;
		static  Color gray24;
		static  Color gray25;
		static  Color gray26;
		static  Color gray27;
		static  Color gray28;
		static  Color gray29;
		static  Color gray3;
		static  Color gray30;
		static  Color gray31;
		static  Color gray32;
		static  Color gray33;
		static  Color gray34;
		static  Color gray35;
		static  Color gray36;
		static  Color gray37;
		static  Color gray38;
		static  Color gray39;
		static  Color gray4;
		static  Color gray40;
		static  Color gray41;
		static  Color gray42;
		static  Color gray43;
		static  Color gray44;
		static  Color gray45;
		static  Color gray46;
		static  Color gray47;
		static  Color gray48;
		static  Color gray49;
		static  Color gray5;
		static  Color gray50;
		static  Color gray51;
		static  Color gray52;
		static  Color gray53;
		static  Color gray54;
		static  Color gray55;
		static  Color gray56;
		static  Color gray57;
		static  Color gray58;
		static  Color gray59;
		static  Color gray6;
		static  Color gray60;
		static  Color gray61;
		static  Color gray62;
		static  Color gray63;
		static  Color gray64;
		static  Color gray65;
		static  Color gray66;
		static  Color gray67;
		static  Color gray68;
		static  Color gray69;
		static  Color gray7;
		static  Color gray70;
		static  Color gray71;
		static  Color gray72;
		static  Color gray73;
		static  Color gray74;
		static  Color gray75;
		static  Color gray76;
		static  Color gray77;
		static  Color gray78;
		static  Color gray79;
		static  Color gray8;
		static  Color gray80;
		static  Color gray81;
		static  Color gray82;
		static  Color gray83;
		static  Color gray84;
		static  Color gray85;
		static  Color gray86;
		static  Color gray87;
		static  Color gray88;
		static  Color gray89;
		static  Color gray9;
		static  Color gray90;
		static  Color gray91;
		static  Color gray92;
		static  Color gray93;
		static  Color gray94;
		static  Color gray95;
		static  Color gray96;
		static  Color gray97;
		static  Color gray98;
		static  Color gray99;
		static  Color green;
		static  Color green1;
		static  Color green2;
		static  Color green3;
		static  Color green4;
		static  Color green_yellow;
		static  Color grey;
		static  Color grey0;
		static  Color grey1;
		static  Color grey10;
		static  Color grey100;
		static  Color grey11;
		static  Color grey12;
		static  Color grey13;
		static  Color grey14;
		static  Color grey15;
		static  Color grey16;
		static  Color grey17;
		static  Color grey18;
		static  Color grey19;
		static  Color grey2;
		static  Color grey20;
		static  Color grey21;
		static  Color grey22;
		static  Color grey23;
		static  Color grey24;
		static  Color grey25;
		static  Color grey26;
		static  Color grey27;
		static  Color grey28;
		static  Color grey29;
		static  Color grey3;
		static  Color grey30;
		static  Color grey31;
		static  Color grey32;
		static  Color grey33;
		static  Color grey34;
		static  Color grey35;
		static  Color grey36;
		static  Color grey37;
		static  Color grey38;
		static  Color grey39;
		static  Color grey4;
		static  Color grey40;
		static  Color grey41;
		static  Color grey42;
		static  Color grey43;
		static  Color grey44;
		static  Color grey45;
		static  Color grey46;
		static  Color grey47;
		static  Color grey48;
		static  Color grey49;
		static  Color grey5;
		static  Color grey50;
		static  Color grey51;
		static  Color grey52;
		static  Color grey53;
		static  Color grey54;
		static  Color grey55;
		static  Color grey56;
		static  Color grey57;
		static  Color grey58;
		static  Color grey59;
		static  Color grey6;
		static  Color grey60;
		static  Color grey61;
		static  Color grey62;
		static  Color grey63;
		static  Color grey64;
		static  Color grey65;
		static  Color grey66;
		static  Color grey67;
		static  Color grey68;
		static  Color grey69;
		static  Color grey7;
		static  Color grey70;
		static  Color grey71;
		static  Color grey72;
		static  Color grey73;
		static  Color grey74;
		static  Color grey75;
		static  Color grey76;
		static  Color grey77;
		static  Color grey78;
		static  Color grey79;
		static  Color grey8;
		static  Color grey80;
		static  Color grey81;
		static  Color grey82;
		static  Color grey83;
		static  Color grey84;
		static  Color grey85;
		static  Color grey86;
		static  Color grey87;
		static  Color grey88;
		static  Color grey89;
		static  Color grey9;
		static  Color grey90;
		static  Color grey91;
		static  Color grey92;
		static  Color grey93;
		static  Color grey94;
		static  Color grey95;
		static  Color grey96;
		static  Color grey97;
		static  Color grey98;
		static  Color grey99;
		static  Color honeydew;
		static  Color honeydew1;
		static  Color honeydew2;
		static  Color honeydew3;
		static  Color honeydew4;
		static  Color hot_pink;
		static  Color hot_pink1;
		static  Color hot_pink2;
		static  Color hot_pink3;
		static  Color hot_pink4;
		static  Color indian_red;
		static  Color indian_red1;
		static  Color indian_red2;
		static  Color indian_red3;
		static  Color indian_red4;
		static  Color ivory;
		static  Color ivory1;
		static  Color ivory2;
		static  Color ivory3;
		static  Color ivory4;
		static  Color khaki;
		static  Color khaki1;
		static  Color khaki2;
		static  Color khaki3;
		static  Color khaki4;
		static  Color lavender;
		static  Color lavender_blush;
		static  Color lavender_blush1;
		static  Color lavender_blush2;
		static  Color lavender_blush3;
		static  Color lavender_blush4;
		static  Color lawn_green;
		static  Color lemon_chiffon;
		static  Color lemon_chiffon1;
		static  Color lemon_chiffon2;
		static  Color lemon_chiffon3;
		static  Color lemon_chiffon4;
		static  Color light_blue;
		static  Color light_blue1;
		static  Color light_blue2;
		static  Color light_blue3;
		static  Color light_blue4;
		static  Color light_coral;
		static  Color light_cyan;
		static  Color light_cyan1;
		static  Color light_cyan2;
		static  Color light_cyan3;
		static  Color light_cyan4;
		static  Color light_goldenrod;
		static  Color light_goldenrod1;
		static  Color light_goldenrod2;
		static  Color light_goldenrod3;
		static  Color light_goldenrod4;
		static  Color light_goldenrod_yellow;
		static  Color light_gray;
		static  Color light_green;
		static  Color light_grey;
		static  Color light_pink;
		static  Color light_pink1;
		static  Color light_pink2;
		static  Color light_pink3;
		static  Color light_pink4;
		static  Color light_salmon;
		static  Color light_salmon1;
		static  Color light_salmon2;
		static  Color light_salmon3;
		static  Color light_salmon4;
		static  Color light_sea_green;
		static  Color light_sky_blue;
		static  Color light_sky_blue1;
		static  Color light_sky_blue2;
		static  Color light_sky_blue3;
		static  Color light_sky_blue4;
		static  Color light_slate_blue;
		static  Color light_slate_gray;
		static  Color light_slate_grey;
		static  Color light_steel_blue;
		static  Color light_steel_blue1;
		static  Color light_steel_blue2;
		static  Color light_steel_blue3;
		static  Color light_steel_blue4;
		static  Color light_yellow;
		static  Color light_yellow1;
		static  Color light_yellow2;
		static  Color light_yellow3;
		static  Color light_yellow4;
		static  Color lime_green;
		static  Color linen;
		static  Color magenta;
		static  Color magenta1;
		static  Color magenta2;
		static  Color magenta3;
		static  Color magenta4;
		static  Color maroon;
		static  Color maroon1;
		static  Color maroon2;
		static  Color maroon3;
		static  Color maroon4;
		static  Color medium_aquamarine;
		static  Color medium_blue;
		static  Color medium_orchid;
		static  Color medium_orchid1;
		static  Color medium_orchid2;
		static  Color medium_orchid3;
		static  Color medium_orchid4;
		static  Color medium_purple;
		static  Color medium_purple1;
		static  Color medium_purple2;
		static  Color medium_purple3;
		static  Color medium_purple4;
		static  Color medium_sea_green;
		static  Color medium_slate_blue;
		static  Color medium_spring_green;
		static  Color medium_turquoise;
		static  Color medium_violet_red;
		static  Color midnight_blue;
		static  Color mint_cream;
		static  Color misty_rose;
		static  Color misty_rose1;
		static  Color misty_rose2;
		static  Color misty_rose3;
		static  Color misty_rose4;
		static  Color moccasin;
		static  Color navajo_white;
		static  Color navajo_white1;
		static  Color navajo_white2;
		static  Color navajo_white3;
		static  Color navajo_white4;
		static  Color navy;
		static  Color navy_blue;
		static  Color old_lace;
		static  Color olive_drab;
		static  Color olive_drab1;
		static  Color olive_drab2;
		static  Color olive_drab3;
		static  Color olive_drab4;
		static  Color orange;
		static  Color orange1;
		static  Color orange2;
		static  Color orange3;
		static  Color orange4;
		static  Color orange_red;
		static  Color orange_red1;
		static  Color orange_red2;
		static  Color orange_red3;
		static  Color orange_red4;
		static  Color orchid;
		static  Color orchid1;
		static  Color orchid2;
		static  Color orchid3;
		static  Color orchid4;
		static  Color pale_goldenrod;
		static  Color pale_green;
		static  Color pale_green1;
		static  Color pale_green2;
		static  Color pale_green3;
		static  Color pale_green4;
		static  Color pale_turquoise;
		static  Color pale_turquoise1;
		static  Color pale_turquoise2;
		static  Color pale_turquoise3;
		static  Color pale_turquoise4;
		static  Color pale_violet_red;
		static  Color pale_violet_red1;
		static  Color pale_violet_red2;
		static  Color pale_violet_red3;
		static  Color pale_violet_red4;
		static  Color papaya_whip;
		static  Color peach_puff;
		static  Color peach_puff1;
		static  Color peach_puff2;
		static  Color peach_puff3;
		static  Color peach_puff4;
		static  Color peru;
		static  Color pink;
		static  Color pink1;
		static  Color pink2;
		static  Color pink3;
		static  Color pink4;
		static  Color plum;
		static  Color plum1;
		static  Color plum2;
		static  Color plum3;
		static  Color plum4;
		static  Color powder_blue;
		static  Color purple;
		static  Color purple1;
		static  Color purple2;
		static  Color purple3;
		static  Color purple4;
		static  Color red;
		static  Color red1;
		static  Color red2;
		static  Color red3;
		static  Color red4;
		static  Color rosy_brown;
		static  Color rosy_brown1;
		static  Color rosy_brown2;
		static  Color rosy_brown3;
		static  Color rosy_brown4;
		static  Color royal_blue;
		static  Color royal_blue1;
		static  Color royal_blue2;
		static  Color royal_blue3;
		static  Color royal_blue4;
		static  Color saddle_brown;
		static  Color salmon;
		static  Color salmon1;
		static  Color salmon2;
		static  Color salmon3;
		static  Color salmon4;
		static  Color sandy_brown;
		static  Color sea_green;
		static  Color sea_green1;
		static  Color sea_green2;
		static  Color sea_green3;
		static  Color sea_green4;
		static  Color seashell;
		static  Color seashell1;
		static  Color seashell2;
		static  Color seashell3;
		static  Color seashell4;
		static  Color sienna;
		static  Color sienna1;
		static  Color sienna2;
		static  Color sienna3;
		static  Color sienna4;
		static  Color sky_blue;
		static  Color sky_blue1;
		static  Color sky_blue2;
		static  Color sky_blue3;
		static  Color sky_blue4;
		static  Color slate_blue;
		static  Color slate_blue1;
		static  Color slate_blue2;
		static  Color slate_blue3;
		static  Color slate_blue4;
		static  Color slate_gray;
		static  Color slate_gray1;
		static  Color slate_gray2;
		static  Color slate_gray3;
		static  Color slate_gray4;
		static  Color slate_grey;
		static  Color snow;
		static  Color snow1;
		static  Color snow2;
		static  Color snow3;
		static  Color snow4;
		static  Color spring_green;
		static  Color spring_green1;
		static  Color spring_green2;
		static  Color spring_green3;
		static  Color spring_green4;
		static  Color steel_blue;
		static  Color steel_blue1;
		static  Color steel_blue2;
		static  Color steel_blue3;
		static  Color steel_blue4;
		static  Color tan;
		static  Color tan1;
		static  Color tan2;
		static  Color tan3;
		static  Color tan4;
		static  Color thistle;
		static  Color thistle1;
		static  Color thistle2;
		static  Color thistle3;
		static  Color thistle4;
		static  Color tomato;
		static  Color tomato1;
		static  Color tomato2;
		static  Color tomato3;
		static  Color tomato4;
		static  Color turquoise;
		static  Color turquoise1;
		static  Color turquoise2;
		static  Color turquoise3;
		static  Color turquoise4;
		static  Color violet;
		static  Color violet_red;
		static  Color violet_red1;
		static  Color violet_red2;
		static  Color violet_red3;
		static  Color violet_red4;
		static  Color wheat;
		static  Color wheat1;
		static  Color wheat2;
		static  Color wheat3;
		static  Color wheat4;
		static  Color white;
		static  Color white_smoke;
		static  Color yellow;
		static  Color yellow1;
		static  Color yellow2;
		static  Color yellow3;
		static  Color yellow4;
		static  Color yellow_green;


		



	};

}

#endif // X11_H

