// TestMyAddDll.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "mclmcr.h"
#include "mclcppclass.h"
#include "libmyadd2.h"


int _tmain(int argc, _TCHAR* argv[])
{

        std::cout << "Hello world!" << std::endl;
        /* Initialize the MCR */ 
       /* if( !mclInitializeApplication(NULL,0) ) 
        { 
                std::cout << "Could not initialize the application!" << std::endl;
                return -1; 
        } */

        // initialize lib
        if( !libmyadd2Initialize())
        {
                std::cout << "Could not initialize libmyadd2!" << std::endl;
                return -1; 
        }

        try
        {
        // declare and initialize a
        mwArray a(2, 2,  mxDOUBLE_CLASS);
        double *aData;
        aData = new double[4];
        int i;
        for( i=0; i<4; ++i)
        {
                aData[i] = 1.0*i;
        }
        // print output
        std::cout << "a = " << std::endl;
        std::cout << aData[0] << ",/t" << aData[1] << std::endl;
        std::cout << aData[2] << ",/t" << aData[3] << std::endl;

        a.SetData(aData, 4);

        // declare and initialize b
        mwArray b(2, 2,  mxDOUBLE_CLASS);
        b(1,1) = 11.;
        b(1,2) = 12.;
        b(2,1) = 21.;
        b(2,2) = 22.;

        mwArray y(2, 2,  mxDOUBLE_CLASS);
        mwArray z(2, 2,  mxDOUBLE_CLASS);

        // call the function
        myadd2(2, y, z, a, b);

        // copy data from mwArray to C++ objects

        // allocate outputs
        double *yData, *zData;
        yData = new double[4];
        if( yData == NULL )
        {
                std::cout << "Failed to allocate memory for yData!" << std::endl;
                return -1;
        }

        zData = new double[4];
        if( zData == NULL )
        {
                std::cout << "Failed to allocate memory for zData!" << std::endl;
                return -1;
        }

        // copy data from mwArray to C++
        y.GetData(yData, 4);
        z.GetData(zData, 4);

        // print output
        std::cout << "y = " << std::endl;
        std::cout << yData[0] << ",/t" << yData[1] << std::endl;
        std::cout << yData[2] << ",/t" << yData[3] << std::endl;

        std::cout << "z = " << std::endl;
        std::cout << zData[0] << ",/t" << zData[1] << std::endl;
        std::cout << zData[2] << ",/t" << zData[3] << std::endl;

        
        // deallocate memory
        delete [] aData;
        delete [] zData;
        delete [] yData;
        }
        catch( const mwException& e)
        {
          std::cerr << e.what() << std::endl;
                  
        }
        // terminate the lib
        libmyadd2Terminate();

        // terminate MCR
        mclTerminateApplication();


        return 0;
}
