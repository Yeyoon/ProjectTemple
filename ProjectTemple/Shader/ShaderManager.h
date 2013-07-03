///////////////////////////////////////////////////////////////
// Filename:	ShaderManager.h
// Author:		Daniel Cossu
// Company:		Ripe Tomato Studios
///////////////////////////////////////////////////////////////
#ifndef __SHADERMANAGER_H_
#define __SHADERMANAGER_H_

#include <Scene\Texture.h>
#include <Shader\LightShader.h>
#include <Shader\TextureShader.h>
#include <Scene\Camera.h>
#include <Scene\Light.h>

namespace Engine
{
	class ShaderManager
	{
		friend class Overlord;
	private:
		LightShader* m_light;
		TextureShader* m_texture;

		D3DXMATRIX m_world, m_view, m_proj;
		Light* m_currentLight;
	public:
		ShaderManager(void);
		~ShaderManager(void);

		D3DXMATRIX GetWorldMatrix(void){return m_world;}
		D3DXMATRIX GetViewMatrix(void){return m_view;}
		D3DXMATRIX GetProjectionMatrix(void){return m_proj;}

		//Functions to store all possible data for shaders.
		void SetWorldMatrix(D3DXMATRIX world);
		void SetViewMatrix(D3DXMATRIX view);
		void SetProjectionMatrix(D3DXMATRIX proj);
		void SetAllMatrices(D3DXMATRIX world, D3DXMATRIX view, D3DXMATRIX proj);
		void SetLight(Light* light);

		//Functions to render the shaders using whichever data they need.
		void RenderTexture(int index, Texture* texture);
		void RenderLight(int index, Texture* texture, Texture* bump=NULL, Texture* spec=NULL, Texture* alpha=NULL);
		//void RenderMultiTexture(ID3D11ShaderResourceView* texture1, ID3D11ShaderResourceView* texture2, int index);
	};
};
#endif //__SHADERMANAGER_H_