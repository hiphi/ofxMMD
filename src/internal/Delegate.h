/* ----------------------------------------------------------------- */
/*                                                                   */
/*  Copyright (c) 2010-2012  hkrn                                    */
/*                                                                   */
/* All rights reserved.                                              */
/*                                                                   */
/* Redistribution and use in source and binary forms, with or        */
/* without modification, are permitted provided that the following   */
/* conditions are met:                                               */
/*                                                                   */
/* - Redistributions of source code must retain the above copyright  */
/*   notice, this list of conditions and the following disclaimer.   */
/* - Redistributions in binary form must reproduce the above         */
/*   copyright notice, this list of conditions and the following     */
/*   disclaimer in the documentation and/or other materials provided */
/*   with the distribution.                                          */
/* - Neither the name of the MMDAI project team nor the names of     */
/*   its contributors may be used to endorse or promote products     */
/*   derived from this software without specific prior written       */
/*   permission.                                                     */
/*                                                                   */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND            */
/* CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,       */
/* INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF          */
/* MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE          */
/* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS */
/* BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,          */
/* EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED   */
/* TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON */
/* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,   */
/* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY    */
/* OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE           */
/* POSSIBILITY OF SUCH DAMAGE.                                       */
/* ----------------------------------------------------------------- */

#ifndef DELEGATE_H
#define DELEGATE_H

#include "ofMain.h"

#include <stdio.h>

#include "Renderer.h"
#include "util.h"
#include "Common.h"

namespace internal {

	class Delegate : public vpvl::gl2::Renderer::IDelegate
{
public:
	vector<ofImage*>imgAry;
    Delegate(/*QGLWidget *widget*/)
        //: m_widget(widget)
    {
		//texUtils = new ExUtoS();
    }
    ~Delegate() {
    }

    bool uploadTexture(const std::string &path, GLuint &textureID, bool isToon) {
		//QString pathString = QString::fromLocal8Bit(path.c_str());path
		//path.replace("\\", "/");
        //QFileInfo info(pathString);
		/*if (info.isDir() || !info.exists()) {
            qWarning("Loading texture %s doesn't exists", qPrintable(info.absoluteFilePath()));
            return false;
        }
        QImage image = QImage(pathString).rgbSwapped();
        if (image.isNull()) {
            qWarning("Loading texture %s cannot decode", qPrintable(info.absoluteFilePath()));
            return false;
        }
        if (path.find(".sph") != string::npos || path.find(".spa") != string::npos) {
            QTransform transform;
            transform.scale(1, -1);
            image = image.transformed(transform);
        }*/
        //QGLContext::BindOptions options = QGLContext::LinearFilteringBindOption|QGLContext::InvertedYBindOption;
        //textureID = m_widget->bindTexture(QGLWidget::convertToGLFormat(image), GL_TEXTURE_2D,
        //                                  image.depth() == 32 ? GL_RGBA : GL_RGB, options);
		ofImage *img = new ofImage();
		img->loadImage(path);
		imgAry.push_back(img);
		glGenTextures(1, &textureID);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 
					 0, 
					 img->getTextureReference().getTextureData().glTypeInternal, 
					 img->getWidth(), img->getHeight(), 
					 0, 
					 img->getTextureReference().getTextureData().glType, 
					 GL_UNSIGNED_BYTE, 
					 img->getPixels()
		);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		
        if (!isToon) {
            glTexParameteri(textureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(textureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
		glBindTexture(GL_TEXTURE_2D, 0);
		
		/*ImageLoader* iLoader = new ImageLoader();
		textureID = iLoader->loadImage(path);
		
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glBindTexture(GL_TEXTURE_2D, textureID);
		
        if (!isToon) {
            glTexParameteri(textureID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(textureID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        //qDebug("Loaded a texture (ID=%d): \"%s\"", textureID, qPrintable(pathString));
		printf("Loaded a texture (ID=%d): \"%s\"\n", textureID, path.c_str());
		glBindTexture(GL_TEXTURE_2D, 0);*/
        return textureID != 0;
    }
    bool uploadToonTexture(const std::string &name, const std::string &dir, GLuint &textureID) {
       /* const QString &filename = QString::fromLocal8Bit(name.c_str());
        QString path = QString::fromLocal8Bit(dir.c_str()) + "/" + filename;
        path.replace("\\", "/");
        if (!QFile::exists(path))
            path = QString(":/textures/%1").arg(filename);
        return uploadTexture(std::string(path.toLocal8Bit()), textureID, true);*/
		//printf("uploadToonTexture\n");
		string path = dir + "/" + name;
		printf("uploadToonTexture:%s\n",path.c_str());
		return uploadTexture(path, textureID, true);
		//return true;
    }
	
    const std::string loadShader(vpvl::gl2::Renderer::ShaderType type) {
		printf("loadShader\n");
        string filename;
        switch (type) {
			case vpvl::gl2::Renderer::kAssetVertexShader:
            filename = "asset.vsh";
            break;
        case vpvl::gl2::Renderer::kAssetFragmentShader:
            filename = "asset.fsh";
            break;
        case vpvl::gl2::Renderer::kEdgeVertexShader:
            filename = "edge.vsh";
            break;
        case vpvl::gl2::Renderer::kEdgeFragmentShader:
            filename = "edge.fsh";
            break;
        case vpvl::gl2::Renderer::kModelVertexShader:
            filename = "model.vsh";
            break;
        case vpvl::gl2::Renderer::kModelFragmentShader:
            filename = "model.fsh";
            break;
        case vpvl::gl2::Renderer::kShadowVertexShader:
            filename = "shadow.vsh";
            break;
        case vpvl::gl2::Renderer::kShadowFragmentShader:
            filename = "shadow.fsh";
            break;
        case vpvl::gl2::Renderer::kZPlotVertexShader:
            filename = "zplot.vsh";
            break;
        case vpvl::gl2::Renderer::kZPlotFragmentShader:
            filename = "zplot.fsh";
            break;
        }
		string path = "../../../data/shaders/";
		path.append(filename);
		
		FILE *fp = fopen(path.c_str(),"r");
		if(fp == NULL){
			//error
			return std::string();
		}
		
        if (fp) {
            /*QByteArray bytes = file.readAll();
            file.close();
            log(Renderer::kLogInfo, "Loaded a shader: %s", qPrintable(path));
            return std::string(reinterpret_cast<const char *>(bytes.constData()), bytes.size());*/
			
			char buf[1024];
			string shaderStr="";
			while((fgets(buf,256,fp))!=NULL){
				//格納された文字を出力
				printf("%s",buf);
				shaderStr.append(buf);
			}
			fclose(fp);
			return shaderStr;
        }else {
			fclose(fp);
            return std::string();
        }
    }
	
    void log(vpvl::gl2::Renderer::LogLevel level, const char *format...) {
		//printf("log ::%s\n",format);
        va_list ap;
        va_start(ap, format);
		char* allocatedBuffer;
		int size = vasprintf(&allocatedBuffer, format, ap);
		
        switch (level) {
        case vpvl::gl2::Renderer::kLogInfo:
        default:
            //qDebug("%s", qPrintable(message));
			printf("log :: %s\n",allocatedBuffer);
            break;
        case vpvl::gl2::Renderer::kLogWarning:
            //qWarning("%s", qPrintable(message));
			printf("warning :: %s\n",allocatedBuffer);
            break;
        }
        va_end(ap);
		free(allocatedBuffer);
    }
    const std::string toUnicode(const uint8_t *value) {
		//return std::string(toQString(value).toUtf8());
		
		std::ostringstream oss;
		oss << value;
		
		return oss.str().c_str();
		//return texUtils->changeStr(oss.str());
    }

private:
	//ExUtoS *texUtils;
    /*QGLWidget *m_widget;

    Q_DISABLE_COPY(Delegate)*/
};

}

#endif // DELEGATE_H
