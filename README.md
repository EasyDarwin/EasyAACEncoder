## EasyAACEncoder ##

**EasyAACEncoder** 是EasyDarwin开源流媒体服务团队整理、开发的一款音频转码到AAC的工具库，目前支持G711a/G711u/G726/PCM等音频格式的转码，跨平台，支持Windows/Linux/arm.


## 调用示例 ##

- **testEasyAACEncoder**：通过EasyAACEncoderAPI对G711A/G711U/G726进行AAC转码；

	Windows编译方法，

    	Visual Studio 2010 编译：./EasyAACEncoder-master/EasyAACEncoder.sln

	Linux编译方法，
		
		chmod +x ./Buildit
		./Buildit


- **ARM版本的EasyAACEncoder库可自行编译**；

## 调用过程 ##
![](http://www.easydarwin.org/skin/easydarwin/images/easyaacencoder20160103.png)


## 特殊说明 ##
EasyAACEncoder目前支持的音视频格式：

	/* Audio Codec */
	enum Law
	{
		Law_ULaw	=	0, 		/**< U law */
		Law_ALaw	=	1, 		/**< A law */
		Law_PCM16	=	2, 		/**< 16 bit uniform PCM values. 原始 pcm 数据 */  
		Law_G726	=	3		/**< G726 */
	};
	
	/* Rate Bits */
	enum Rate
	{
		Rate16kBits=2,	/**< 16k bits per second (2 bits per ADPCM sample) */
		Rate24kBits=3,	/**< 24k bits per second (3 bits per ADPCM sample) */
		Rate32kBits=4,	/**< 32k bits per second (4 bits per ADPCM sample) */
		Rate40kBits=5	/**< 40k bits per second (5 bits per ADPCM sample) */
	};

## 获取更多信息 ##

邮件：[support@easydarwin.org](mailto:support@easydarwin.org) 

WEB：[www.EasyDarwin.org](http://www.easydarwin.org)

Author：破/浪Leo，Arno，Wellsen

Copyright &copy; EasyDarwin.org 2012-2017

![EasyDarwin](http://www.easydarwin.org/skin/easydarwin/images/wx_qrcode.jpg)
