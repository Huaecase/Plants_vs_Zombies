/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Loading.h"
#include "Title.h"
using namespace std;
class HelloWorld : public cocos2d::Scene
{
private:
	Loading* loading;
	Title* title;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void updateSun(float delta);
	void updateZombie(float delta);
	void updateCD(float delta);
	void updateProgressBar(float delta);
	void checkWinAndLose(float delta);

	void preLoading();

	void ResourceCallBack(cocos2d::Texture2D *texture);
	void GameIn(float t);
	string & replace_all(string & str, const string & old_value, const string & new_value);
	void getFiles(string prePath, string path, vector<string>& files, vector<string>& ownname);
	int loadingSprite = 0;
	int tot_loadingSprite = 0;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	void moveCamera(float delta);
	void moveCameraRight(float delta);
	void moveCameraLeft(float delta);
	void LoadingCard(Node* pSender);
	static DrawNode* CDRect;
};

#endif // __HELLOWORLD_SCENE_H__
