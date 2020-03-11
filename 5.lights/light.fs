//
//  light.fs
//  OpenGLLighting
//
//  Created by Sushant Kondguli on 3/9/20.
//  Copyright © 2020 learning. All rights reserved.
//

#version 330 core
out vec4 color;
uniform vec3 lightColor;
void main()
{
    color = vec4(lightColor, 1.0); // set all 4 vector values to 1.0
}
