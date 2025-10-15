//
// Created by Ben on 2/10/2023.
//

#pragma once

#include "GLM/vec3.hpp"
#include "GLM/vec4.hpp"
#include <vector>

#include "FastNoiseLite.h"

namespace cs4722 {
/**
 *  \brief A height_field represents a two dimensional arrays of numbers that represent heights.
 *
 *  This base class is abstract, the `generate` function is pure and virtual.
 *  The intent is that each subclass will provide a way to generate the date in the field.
 */
    class HeightField {

    public:
        /// The number of points in each dimension of the height field.
        int width, depth;
        /// Stores the actual height values.
        double *grid;
        /** \brief How the height field will be scaled from a size of 1 by 1 by 1.
         *
         * Used by the altitude function that returns a scaled and translated height
         * based on scaled and translated
         * coordinates.
         */
        glm::vec3 scale = glm::vec3(1, 1, 1);
        /** \brief How the height field will be scaled from a size of 1 by 1 by 1.
         *
         * Used by the altitude function that returns a scaled and translated height
         * based on scaled and translated
         * coordinates.
         */
        glm::vec3 translate = glm::vec3(0, 0, 0);

        /// Allocates space to the `grid`..
        HeightField(int width, int depth)
                : width(width), depth(depth) {
            grid = new double[width * depth];
        }

        /// Provides data to `grid`.
        virtual void generate() = 0;

        /// Returns a scaled and translated height based on scaled and translated coordinates.
        double altitude(double x, double z);

        /// Generates a vector of triangle vertices suitable for use in shape.
        std::vector<glm::vec4> *triangleVertices();

        virtual std::vector<glm::vec4> *normals();

        /// returns the lowest point in the height field with coordinates scaled and translated.
        glm::vec4 low_point();

    };


/// Implements `generate` by using the Fast Noise Light library.

/**
 * The attributes in this class are just parameters that can be set for
 * a noise generating object.
 */
    class HeightFieldFNL : public HeightField {

    public:
        /// Holds a value for an attribute of FastNoiseLight noise, initialized to the default
        FastNoiseLite::NoiseType noiseType = FastNoiseLite::NoiseType_Perlin;
        /// Holds a value for an attribute of FastNoiseLight noise, initialized to the default
        FastNoiseLite::FractalType fractalType = FastNoiseLite::FractalType_None;
        /// Holds a value for an attribute of FastNoiseLight noise, initialized to the default
        double frequency = 0.01;
        /// Holds a value for an attribute of FastNoiseLight noise, initialized to the default
        double amp = .5;
        /// Holds a value for an attribute of FastNoiseLight noise, initialized to the default
        int numberOfOctaves = 4;
        /// Holds a value for an attribute of FastNoiseLight noise, initialized to the default
        double gain = .5;
        /// Holds a value for an attribute of FastNoiseLight noise, initialized to the default
        double fractalWeightedStrength = 0.0;
        /// Holds a value for an attribute of FastNoiseLight noise, initialized to the default
        double pingPongStrength = 2.0;
        /// Holds a value for an attribute of FastNoiseLight noise, initialized to the default
        double fractalLacunarity = 2.0;
        /// This is the default seed used for noise generation in Fast Noise Light
        /// Change this value to get different terrains.
        int seed = 1337;


        HeightFieldFNL(int width, int height)
                : HeightField(width, height) {

        }

        virtual void generate();

        virtual std::vector<glm::vec4> *normals();

    private:
        /// obsolete
//        void generate_v1();

        FastNoiseLite* generator();

    };


/**
 * \brief Generates height fields using the C random number generator.
 *
 * Not all that useful
 */
    class HeightFieldRand : public HeightField {
    public:

        unsigned int seed = 123456;

        HeightFieldRand(int width, int height)
                : HeightField(width, height) {

        }


        virtual void generate();
    };

}