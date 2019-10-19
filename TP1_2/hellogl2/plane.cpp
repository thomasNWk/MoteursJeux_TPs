/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "plane.h"
#include <qmath.h>
#include <QTime>
#include <iostream>

float randomFloat(float min, float max) {
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

Plane::Plane()
    : m_count(0)
{
    m_data.resize(2500 * 6);

    srand(time(NULL));

    GLfloat x = -0.212f;
    GLfloat y = -0.212;
    GLfloat z = 0.0f;

    GLfloat incr = 0.04f;

    QVector3D vertices[16][16];
    QVector2D uvs[16][16];

    for(int i = 0; i < 16; i++) {
        for(int j = 0; j < 16; j++) {
            vertices[i][j] = QVector3D(x + i*incr, y + j*incr, randomFloat(0.0f, 0.1f));
            uvs[i][j] = QVector2D((float)i / 15.0f, (float)j / 15.0f);
            //std::cout << "x = " << vertices[i][j].x() << "y = " << vertices[i][j].y() << "z = " << vertices[i][j].z()<<  std::endl;
        }
    }

    for(int i = 0; i < 15; i++) {
        for(int j = 0; j < 15; j++) {
           /*quad(vertices[i][j].x(), vertices[i][j].y(),
                vertices[i+1][j].x(), vertices[i+1][j].y(),
                vertices[i+1][j+1].x(), vertices[i+1][j+1].y(),
                vertices[i][j+1].x(), vertices[i][j+1].y());*/
            quad(vertices[i][j],
                 vertices[i+1][j],
                 vertices[i+1][j+1],
                 vertices[i][j+1],
                 uvs[i][j],
                 uvs[i+1][j],
                 uvs[i+1][j+1],
                 uvs[i][j+1]);

        }
    }
}

void Plane::add(const QVector3D &v, const QVector3D &n, const QVector2D &uvs)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    *p++ = uvs.x();
    *p++ = uvs.y();
    m_count += 8;
}

void Plane::quad(QVector3D v1, QVector3D v2, QVector3D v3, QVector3D v4, QVector2D uv1, QVector2D uv2, QVector2D uv3, QVector2D uv4)
{
    QVector3D n = QVector3D::normal(v4 - v1, v2 - v1);

    add(v1, n, uv1);
    add(v4, n, uv4);
    add(v2, n, uv2);

    add(v3, n, uv3);
    add(v2, n, uv2);
    add(v4, n, uv4);
}
