////////////////////////////////////////////////////////////////////////////////
// SoftKinetic DepthSense SDK
//
// COPYRIGHT AND CONFIDENTIALITY NOTICE - SOFTKINETIC CONFIDENTIAL
// INFORMATION
//
// All rights reserved to SOFTKINETIC SENSORS NV (a
// company incorporated and existing under the laws of Belgium, with
// its principal place of business at Boulevard de la Plainelaan 11,
// 1050 Brussels (Belgium), registered with the Crossroads bank for
// enterprises under company number 0811 341 454 - "Softkinetic
// Sensors").
//
// The source code of the SoftKinetic DepthSense Camera Drivers is
// proprietary and confidential information of Softkinetic Sensors NV.
//
// For any question about terms and conditions, please contact:
// info@softkinetic.com Copyright (c) 2002-2015 Softkinetic Sensors NV
////////////////////////////////////////////////////////////////////////////////

#include <WinSock2.h>
#ifdef _MSC_VER
#include <windows.h>
#endif

#include <stdio.h>
#include <vector>
#include <exception>
#include <engine.h>
#include <cmath>
#include <DepthSense.hxx>
#include "matrix.h"
#include <stdlib.h>
#include <string.h>

//#include <winsock.h>

//#include <unistd.h>
#include <sys/types.h> 
//#include <sys/socket.h>
//#include <netinet/in.h>

int sockfd;
struct sockaddr_in cli_addr;

void setupServer();
//void sendData(data)


using namespace DepthSense;
using namespace std;

Context g_context;
DepthNode g_dnode;
uint32_t g_dFrames = 0;

bool g_bDeviceFound = false;

ProjectionHelper* g_pProjHelper = NULL;
StereoCameraParameters g_scp;


/*----------------------------------------------------------------------------*/
// New depth sample event handler
void onNewDepthSample(DepthNode node, DepthNode::NewSampleReceivedData data)
{
	int i = 0;
	Engine *ep = engOpen(NULL);
	mxArray *x_array = mxCreateDoubleMatrix(38400, 1, mxREAL);
	mxArray *y_array = mxCreateDoubleMatrix(38400, 1, mxREAL);
	mxArray *z_array = mxCreateDoubleMatrix(38400, 1, mxREAL);		//this is all matlab stuff
	mxArray *fz_array = mxCreateDoubleMatrix(1, 1, mxREAL);
	double *px = mxGetPr(x_array);
	double *py = mxGetPr(y_array);
	double *pz = mxGetPr(z_array);
	double *fz = mxGetPr(fz_array);
	

	char x1[10000];
	int x2[10000];
	int x3[10000];
	int x4[8400];

	int y1[10000];
	int y2[10000];
	int y3[10000];
	int y4[8400];

	int z1[10000];
	int z2[10000];
	int z3[10000];
	int z4[8400];

	int32_t w, h;
	FrameFormat_toResolution(data.captureConfiguration.frameFormat, &w, &h);

	
	for (i = 0; i < 76798; i = i + 2) {
		px[i / 2] = data.vertices[i].x;
		py[i / 2] = data.vertices[i].y;
		pz[i / 2] = data.vertices[i].z;
	}

/*
		if (i < 20000) {
			x1[i / 2] = data.vertices[i].x;
			y1[i / 2] = data.vertices[i].y;
			z1[i / 2] = data.vertices[i].z;
		}
	}
			if (i < 40000) {
			x2[i / 2] = data.vertices[i].x;
			y2[i / 2] = data.vertices[i].y;
			z2[i / 2] = data.vertices[i].z;
		}
		if (i < 60000) {
			x3[i / 2] = data.vertices[i].x;
			y3[i / 2] = data.vertices[i].y;
			z3[i / 2] = data.vertices[i].z;
		}
		if (i < 80000) {
			x4[i / 2] = data.vertices[i].x;
			y4[i / 2] = data.vertices[i].y;
			z4[i / 2] = data.vertices[i].z;
		}

	}
	*/
	
		//memcpy(&x1, &data.vertices[0].x , sizeof(x1));
		
		/*
		memcpy(&x2, px+sizeof(x1), sizeof(x2));
		memcpy(&x3, px+sizeof(x2), sizeof(x3));
		memcpy(&x4, px+sizeof(x3), sizeof(x4));

		memcpy(&y1, px, sizeof(x1));
		memcpy(&y2, px + sizeof(x1), sizeof(x2));
		memcpy(&y3, px + sizeof(x2), sizeof(x3));
		memcpy(&y4, px + sizeof(x3), sizeof(x4));

		memcpy(&y1, px, sizeof(x1));
		memcpy(&y2, px + sizeof(x1), sizeof(x2));
		memcpy(&y3, px + sizeof(x2), sizeof(x3));
		memcpy(&y4, px + sizeof(x3), sizeof(x4));
		*/
		
		//int test[100];
	
	
	//int n;
	//n = sendto(sockfd, "MTRN4110KBJT", 12, 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));


	//int temp[] = { 256, 567, 890 };
	//n = sendto(sockfd, (const char*)&temp, sizeof(temp), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	
	//n = sendto(sockfd, x1, sizeof(x1), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	/*
	n = sendto(sockfd, (const char*)&x2, sizeof(x2), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	n = sendto(sockfd, (const char*)&x3, sizeof(x3), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	n = sendto(sockfd, (const char*)&x4, sizeof(x4), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	
	n = sendto(sockfd, (const char*)&y1, sizeof(y1), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	n = sendto(sockfd, (const char*)&y2, sizeof(y2), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	n = sendto(sockfd, (const char*)&y3, sizeof(y3), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	n = sendto(sockfd, (const char*)&y4, sizeof(y4), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));

	n = sendto(sockfd, (const char*)&z1, sizeof(z1), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	n = sendto(sockfd, (const char*)&z2, sizeof(z2), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	n = sendto(sockfd, (const char*)&z3, sizeof(z3), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	n = sendto(sockfd, (const char*)&z4, sizeof(z4), 0, (struct sockaddr *) &cli_addr, sizeof(cli_addr));
	*/	
	printf("Z#%u: %d \n", g_dFrames, x1[100]);

    g_dFrames++;
	fz[1] = g_dFrames;

	engPutVariable(ep, "fz", fz_array);
	engPutVariable(ep, "x", x_array);
	engPutVariable(ep, "y", y_array);
	engPutVariable(ep, "z", z_array);
	engEvalString(ep, "scatt");
	//engEvalString(ep, "axis([0, 76800, 0, 76800, 0, -500])");



	//delete px; 
	//delete py; 
	//delete pz;
	mxDestroyArray(x_array);
	mxDestroyArray(y_array);
	mxDestroyArray(z_array);
    // Quit the main loop after 200 depth frames received
	//if (g_dFrames == 200)
     //   g_context.quit();


}

/*----------------------------------------------------------------------------*/

void setupServer() {
	int ServPortNum = 4001;
	int CliPortNum = 4002;
	int newsockfd;
	///socklen_t clilen;
	struct sockaddr_in serv_addr;
	int n;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) {
		printf("Error opening socket\n");
	}

	memset((char *)&serv_addr,0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(ServPortNum);

	memset((char *)&cli_addr,0, sizeof(cli_addr));
	cli_addr.sin_family = AF_INET;
	cli_addr.sin_addr.s_addr = inet_addr("192.168.1.107");
	cli_addr.sin_port = htons(CliPortNum);

	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
		//printf("ERROR on binding\n");


	printf("Bound\n");


}
/*----------------------------------------------------------------------------*/
void configureDepthNode()
{
    g_dnode.newSampleReceivedEvent().connect(&onNewDepthSample);

    DepthNode::Configuration config = g_dnode.getConfiguration();
    config.frameFormat = FRAME_FORMAT_QVGA;
    config.framerate = 25;
    config.mode = DepthNode::CAMERA_MODE_CLOSE_MODE;
    config.saturation = true;

    g_dnode.setEnableVertices(true);
    try 
    {
        g_context.requestControl(g_dnode,0);

        g_dnode.setConfiguration(config);
    }
    catch (ArgumentException& e)
    {
        printf("Argument Exception: %s\n",e.what());
    }
    catch (UnauthorizedAccessException& e)
    {
        printf("Unauthorized Access Exception: %s\n",e.what());
    }
    catch (IOException& e)
    {
        printf("IO Exception: %s\n",e.what());
    }
    catch (InvalidOperationException& e)
    {
        printf("Invalid Operation Exception: %s\n",e.what());
    }
    catch (ConfigurationException& e)
    {
        printf("Configuration Exception: %s\n",e.what());
    }
    catch (StreamingException& e)
    {
        printf("Streaming Exception: %s\n",e.what());
    }
    catch (TimeoutException&)
    {
        printf("TimeoutException\n");
    }

}

/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
void configureNode(Node node)
{
    if ((node.is<DepthNode>())&&(!g_dnode.isSet()))
    {
        g_dnode = node.as<DepthNode>();
        configureDepthNode();
        g_context.registerNode(node);
    }

}

/*----------------------------------------------------------------------------*/
void onNodeConnected(Device device, Device::NodeAddedData data)
{
    configureNode(data.node);
}

/*----------------------------------------------------------------------------*/
void onNodeDisconnected(Device device, Device::NodeRemovedData data)
{
  
    if (data.node.is<DepthNode>() && (data.node.as<DepthNode>() == g_dnode))
        g_dnode.unset();
    printf("Node disconnected\n");
}

/*----------------------------------------------------------------------------*/
void onDeviceConnected(Context context, Context::DeviceAddedData data)
{
    if (!g_bDeviceFound)
    {
        data.device.nodeAddedEvent().connect(&onNodeConnected);
        data.device.nodeRemovedEvent().connect(&onNodeDisconnected);
        g_bDeviceFound = true;
    }
}

/*----------------------------------------------------------------------------*/
void onDeviceDisconnected(Context context, Context::DeviceRemovedData data)
{
    g_bDeviceFound = false;
    printf("Device disconnected\n");
}

/*----------------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
	//setupServer();
	Engine *ep = engOpen(NULL);
	engEvalString(ep, "init_scatt");
    g_context = Context::create("localhost");

    g_context.deviceAddedEvent().connect(&onDeviceConnected);
    g_context.deviceRemovedEvent().connect(&onDeviceDisconnected);

    // Get the list of currently connected devices
    vector<Device> da = g_context.getDevices();

	vector<Node> na = da[0].getNodes();
	configureNode(na[1]);

    g_context.startNodes();

    g_context.run();

    g_context.stopNodes();

    if (g_dnode.isSet()) g_context.unregisterNode(g_dnode);

    if (g_pProjHelper)
        delete g_pProjHelper;

    return 0;
}
