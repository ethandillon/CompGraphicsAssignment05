

#pragma once


#include <list>
#include <GLM/vec3.hpp>
//#include <GLM/ext.hpp>
#include "cs4722/x11.h"
#include "cs4722/shape.h"
#include "cs4722/transform.h"


namespace cs4722
{


    /**
     * \brief Represents common characteristics of surfaces for use in lighting
     *  and shading.
     *
     *
     */
    class Material {
    public:
        cs4722::Color diffuseColor = cs4722::X11::steel_blue,
            ambientColor = cs4722::X11::gray50,
            specularColor = cs4722::X11::olive_drab;
        double shininess = 20.0;
        float specularStrength = 1.0;
        bool reflecting = false;
    };


    /**
     * \brief Represents a geometric object based on a standard shape.
     *
     * An `object` instance 
     */
    class Artifact {



        public:

        Material surfaceMaterial;

        // Transformation animationTransform;
        Transformation* worldTransformation;
        Shape* theShape = nullptr;
        bool shapeIsShared = false;
        int textureUnit = 0;
        int surfaceEffect = 0;

        Artifact* parent = nullptr;
        std::list<Artifact*> children;

        bool visible = true;

        /**
         *  Initialize Artifact with a plain Transformation as the world transformation.
         */
        Artifact();

        /**
         * Initialize Artifact with the specified world transformation.
         */
        explicit Artifact(Transformation* worldTtransformation);
    	
    };


}