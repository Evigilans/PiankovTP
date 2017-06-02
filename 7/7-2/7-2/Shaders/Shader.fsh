//
//  Shader.fsh
//  7-2
//
//  Created by Admin on 19.05.17.
//  Copyright (c) 2017 Egor. All rights reserved.
//

varying lowp vec4 colorVarying;

void main()
{
    gl_FragColor = colorVarying;
}
