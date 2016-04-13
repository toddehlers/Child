

//
//  	miNumLithologyMaps = infile.ReadItem( miNumLithologyMaps, "NUMUPLIFTMAPS" );
//  	miLithologyMapDepthInterval= infile.ReadItem( miLithologyMapDepthInterval, "DEPTHINTERVAL" );
//  	mLithologyMapDepths.setSize( miNumLithologyMaps );
//  	infile.ReadItem( mLithologyMapFilename, sizeof(mLithologyMapFilename), "LITHOMAPFILENAME" );
//    for( int i=0; i<miNumLithologyMaps; i++)
//        {
//          mLithologyMapDepths[i] = i * miLithologyMapDepthInterval;
//           	
//        }
//        
        
// LETS RETHINK THIS.  MAYBE LOAD IN ALL FILES INTO ONE LARGE 2-D ARRAY LENGTH OF #NODES BY 3 LEVELS 
// DO THIS WITH INTEGERS TO SAVE MEMEMORY REQUIREMENTS        
        
        
        
//     mElevNextLithoMap = getz() - miLithologyMapDepthInterval; 
     const int nnodes = meshPtr->getNodeList()->getSize();  // # of nodes on list

// from detachlimero
//getDzDt() - cn->getDzDt();
//	  if( ratediff > 0 )
//	    {
//	      dt = ( cn->getZ



     for( int j=0; j<nnodes; j++ )    //loop through all points  64
      {
 
       mCurrentLithoMap [j] = 1;
          
    std::ifstream LithoKdMapFile;
    std::ifstream LithoKbMapFile;

    char myfilenamekd[120];
    char myfilenamekb[120];
    const char* const nums("0123456789");
    strcpy( myfilenamekd, mLithologyMapFilename );  // start w/ base name...
    strncat(myfilenamekd, &nums[static_cast<int>( static_cast<double>(mCurrentLithoMap[j]/100.0) )], 1);
    strncat(myfilenamekd, &nums[static_cast<int>( fmod(static_cast<double>(mCurrentLithoMap[j]),100.0)/10.0 )], 1);
    strncat(myfilenamekd, &nums[static_cast<int>( fmod(static_cast<double>(mCurrentLithoMap[j]),10.0) )], 1);
    strcpy( myfilenamekb, mLithologyMapFilename );  // start w/ base name...
    strncat(myfilenamekb, &nums[static_cast<int>( static_cast<double>(mCurrentLithoMap[j]/100.0) )], 1);
    strncat(myfilenamekb, &nums[static_cast<int>( fmod(static_cast<double>(mCurrentLithoMap[j]),100.0)/10.0 )], 1);
    strncat(myfilenamekb, &nums[static_cast<int>( fmod(static_cast<double>(mCurrentLithoMap[j]),10.0) )], 1);

    LithoKdMapFile.open( myfilenamekd );
    LithoKbMapFile.open( myfilenamekb );
    if( !LithoKdMapFile.good() )
	{
	  std::cout << "Failed to find KD map file" << myfilenamekd << "\n";
      ReportFatalError("Unable to open KD map file.");
	}

    if(0) std::cout << "The name we want to read is <" << myfilenamekd << ">" << std::endl;

 	if( !LithoKdMapFile.good() )
	{
	  std::cout << "Failed to find KB map file " << myfilenamekb << "\n";
      ReportFatalError("Unable to open KB map file.");
	}

    if(0) std::cout << "The name we want to read is <" << myfilenamekb << ">" << std::endl;

     
     
     
     // set current lithology values
      meshPtr->RenumberIDCanonically();
     const tMesh< tLNode >::tIdArrayNode_t  RNode(*(meshPtr->getNodeList()));

     for( int j=0; j<nnodes; j++ )
    {
      tLNode *cn;
      double local_kd;
      double local_kb;

      cn = RNode[j];
      LithoKdMapFile >> local_kd;
  //    LithoKbMapFile >> local_kb;

      cn->setKD( local_kd );
    //  cn->setKb( local_kb );

    }

     
     
      }  //goes with 'loop through all points  64'
     
     
//       Read the contents of the file and store uplift rate for each node.
//     But first we renumber node IDs "canonically", meaning ordered by 
//     coordinate. This is handled using Arnaud's method, in which an object
//     of type tIdArrayNode_t contains a list of nodes arranged according to
//     ID number.
//    const int nnodes = mp->getNodeList()->getSize();  // # of nodes on list
//    mp->RenumberIDCanonically();
//    const tMesh< tLNode >::tIdArrayNode_t  RNode(*(mp->getNodeList()));
//
//     for( int j=0; j<nnodes; j++ )
//    {
//      tLNode *cn;
//      double local_uplift_rate;
//      cn = RNode[j];
//      upliftRateMapFile >> local_uplift_rate;
//      cn->setUplift( local_uplift_rate );
//    }
        
//	      for( int i=0; i<miNumUpliftMaps; i++ )
//	        upliftTimeFile >> mUpliftMapTimes[i];
//	      upliftTimeFile.close();
 // from Uplift Map initialize
//  case k12:
//	      {
//		  char timesFileName[120];
//          std::ifstream upliftTimeFile;
//	      miNumUpliftMaps = infile.ReadItem( miNumUpliftMaps, "NUMUPLIFTMAPS" );
//	      infile.ReadItem( mUpliftMapFilename, sizeof(mUpliftMapFilename), "UPMAPFILENAME" );
//	      infile.ReadItem( timesFileName, sizeof(timesFileName), "UPTIMEFILENAME" );
//	      if( !upliftTimeFile.good() )
//	      ReportFatalError("Unable to open file containing uplift map times.");
//	      mUpliftMapTimes.setSize( miNumUpliftMaps );
//	      mdNextUpliftMapTime = 0.0;
//	      miCurUpliftMapNum = 0;
//	      for( int i=0; i<miNumUpliftMaps; i++ )
//	        upliftTimeFile >> mUpliftMapTimes[i];
//	      upliftTimeFile.close();
//		  }
//	      break;
 	
  	
  	
  	
// from detachlimero
//getDzDt() - cn->getDzDt();
//	  if( ratediff > 0 )
//	    {
//	      dt = ( cn->getZ




     
     
//     
//     // set current lithology values
//      meshPtr->RenumberIDCanonically();
//     const tMesh< tLNode >::tIdArrayNode_t  RNode(*(meshPtr->getNodeList()));
//
//     for( int j=0; j<nnodes; j++ )
//    {
//      tLNode *cn;
//      double local_kd;
//      double local_kb;
//
//      cn = RNode[j];
//      LithoKdMapFile >> local_kd;
//  //    LithoKbMapFile >> local_kb;
//
//      cn->setKD( local_kd );
//    //  cn->setKb( local_kb );
//
//    }
//
//     
//     
//      }  //goes with 'loop through all points  64'
     
     
//       Read the contents of the file and store uplift rate for each node.
//     But first we renumber node IDs "canonically", meaning ordered by 
//     coordinate. This is handled using Arnaud's method, in which an object
//     of type tIdArrayNode_t contains a list of nodes arranged according to
//     ID number.
//    const int nnodes = mp->getNodeList()->getSize();  // # of nodes on list
//    mp->RenumberIDCanonically();
//    const tMesh< tLNode >::tIdArrayNode_t  RNode(*(mp->getNodeList()));
//
//     for( int j=0; j<nnodes; j++ )
//    {
//      tLNode *cn;
//      double local_uplift_rate;
//      cn = RNode[j];
//      upliftRateMapFile >> local_uplift_rate;
//      cn->setUplift( local_uplift_rate );
//    }
        
//	      for( int i=0; i<miNumUpliftMaps; i++ )
//	        upliftTimeFile >> mUpliftMapTimes[i];
//	      upliftTimeFile.close();
 // from Uplift Map initialize
//  case k12:
//	      {
//		  char timesFileName[120];
//          std::ifstream upliftTimeFile;
//	      miNumUpliftMaps = infile.ReadItem( miNumUpliftMaps, "NUMUPLIFTMAPS" );
//	      infile.ReadItem( mUpliftMapFilename, sizeof(mUpliftMapFilename), "UPMAPFILENAME" );
//	      infile.ReadItem( timesFileName, sizeof(timesFileName), "UPTIMEFILENAME" );
//	      if( !upliftTimeFile.good() )
//	      ReportFatalError("Unable to open file containing uplift map times.");
//	      mUpliftMapTimes.setSize( miNumUpliftMaps );
//	      mdNextUpliftMapTime = 0.0;
//	      miCurUpliftMapNum = 0;
//	      for( int i=0; i<miNumUpliftMaps; i++ )
//	        upliftTimeFile >> mUpliftMapTimes[i];
//	      upliftTimeFile.close();
//		  }
//	      break;
 	
  	
  	
  	


}




/**************************************************************************\
**                 FUNCTIONS FOR CLASS tLithology
\**************************************************************************/

/**************************************************************************\
**
**  tLithology constructors:
**    1. Default
**    2. Input file
**
\**************************************************************************/

//void tLithology::UpdateLithology( tMesh<class tLNode> * meshPtr)
//{
//	// if(1) std::cout << "Greetings from Update Lithology" << std::endl;
//	
//	getUplift;
//	
//	
//	
//	
//	
//}