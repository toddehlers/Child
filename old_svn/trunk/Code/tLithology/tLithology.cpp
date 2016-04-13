/**************************************************************************/
/**
**  @file tLithology.cpp
**  @brief Functions for tLitholgy class
**
**  Class tLithology represents the lithology
**  across a terrain. Class tLithology is designed to embed in a node (
**  similar to tVegCover) the local erodibility parameters kd and kf
**
**
**  Created Feb, 2012, BJY
*/
/**************************************************************************/


#include <assert.h>
#include <vector>
#include "tLithology.h"
#include "../tMesh/tMesh.h"


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

tLithology::tLithology()
  :
  mdKdL(0),
  mdKbL(1)
{}

tLithology::tLithology( tMesh<class tLNode> *meshPtr, const tInputFile &infile )
  :
  mdKdL(0),
  mdKbL(1)
{
//  int i;
//  int j;
  if(1) std::cout << "Greetings from tLithology, initialize" << std::endl;

//    miMaxNumUnits = infile.ReadItem( miMaxNumUnits, "MAXLITHOUNITS" );

// make this numlithounits, the number of layers to be created
    numlithounits = infile.ReadItem( numlithounits, "MAXLITHOUNITS" );
    
    miNumLithologies = infile.ReadItem( miNumLithologies, "NUMLITHOLOGIES" );
    // MAKE NEW FILE WITH lenght=NNODES, and each entry is the number of lithologies (layers) at that point
    

    infile.ReadItem( mPropertyLookUpFilename, sizeof(mPropertyLookUpFilename), "UNITPROPTABLEFILENAME" );
    infile.ReadItem( mLithoBaseElevationFilename, sizeof(mLithoBaseElevationFilename), "LITHOBASELEVATIONFILENAME" );
    infile.ReadItem( mLithoUnitOrderFilename, sizeof(mLithoUnitOrderFilename), "LITHOUNITSORDERFILENAME" );
    
    // read num of grain size for layer creation below
     unsigned num_grain_sizes = infile.ReadInt( "NUMGRNSIZE" );


     const int nnodes = meshPtr->getNodeList()->getSize();  // # of nodes on list
	 // read list of units (in order of increasing depth) for each node
	 std::ifstream LithoKdUnitsFile;
	 char myfilenameunitlist[120];
     strcpy( myfilenameunitlist, mLithoUnitOrderFilename );
     LithoKdUnitsFile.open(myfilenameunitlist);
     if( !LithoKdUnitsFile.good() )
	{
	  std::cout << "Failed to find KD Unil List file" << myfilenameunitlist << "\n";
      ReportFatalError("Unable to open KD Unit List file.");
	}
    if(0) std::cout << "The name we want to read is <" << myfilenameunitlist << ">" << std::endl;


	// read list of depths of contacts for each node
	std::ifstream LithoDepthsFile;
	 char myfilenamedepthlist[120];
     strcpy( myfilenamedepthlist, mLithoBaseElevationFilename );
     LithoDepthsFile.open(myfilenamedepthlist);
     if( !LithoDepthsFile.good() )
	{
	  std::cout << "Failed to find KD depth list file file" << myfilenamedepthlist << "\n";
      ReportFatalError("Unable to open KD Depth List file.");
	}
    if(0) std::cout << "The name we want to read is <" << myfilenamedepthlist << ">" << std::endl;

    std::ifstream KDTableFile;
    
    // initialize layer variables
    KDLookupTable.setSize ( miNumLithologies);
    KBLookupTable.setSize ( miNumLithologies);
//    SedDensityLookupTable.setSize( miNumLithologies);  FOR SVN Version
    SedRockFlagLookupTable.setSize( miNumLithologies);
    DgradeLookupTable.setSize( miNumLithologies);

    KDTableFile.open(mPropertyLookUpFilename);
	      for( int i=0; i<miNumLithologies; i++ )
	      {
	        KDTableFile >> KDLookupTable[i];
	        KDTableFile >> KBLookupTable[i];
//	        KDTableFile >> SedDensityLookupTable[i]; FOR SVN Version
	        KDTableFile >> SedRockFlagLookupTable[i];
	        KDTableFile >> DgradeLookupTable[i];
	      }
	      KDTableFile.close();
		
    meshPtr->RenumberIDCanonically();

   const tMesh< tLNode >::tIdArrayNode_t  RNode(*(meshPtr->getNodeList()));
    for( int i=0; i<nnodes; i++ )
    {
      tLNode *cn;
      cn = RNode[i];
      if( LithoKdUnitsFile.eof() )
          ReportFatalError( "Reached end-of-file while reading lithology points." );
for (int j=0; j<numlithounits; j++)
{
     LithoKdUnitsFile >> LocUnitList;
     // for testing   
//     std::cout << "LocUnitList value = " << LocUnitList << j  << std::endl;
     
     cn->setLithoUnitList(j,LocUnitList);
//     std::cout << "LithoCheck " << numlithounits << miNumLithologies  << std::endl;

     LithoDepthsFile >> LocContactDepths;
//               std::cout << "LocContactDepths value = " << LocContactDepths << j  << std::endl;

	cn->setLithoContactDepths(j,LocContactDepths);
}
    
 
   }




// generate initial array of current INdex, current unit, and contact detph
double LocNextDepth;
int LocUnit;
double lockd;
double lockb;
  erody.setSize( nnodes );
//    	  std::cout << "nnodes" << nnodes << "\n";

for(int i=0; i<nnodes; i++ )
{
	tLNode *cn;
	cn = RNode[i];
	
	cn->setCurrentLithoIndex(0);
	
	LocUnit = cn->getLithoUnitList(0);
	cn->setCurrentLithoUnit(LocUnit);
	
	LocNextDepth = cn->getLithoContactDepths(0);
	cn->setNextContactDepth(LocNextDepth);
	
	lockd = KDLookupTable[LocUnit];
	lockb = KBLookupTable[LocUnit];
//	    std::cout << "KD = " << lockd << "   KB =   " << lockb << "   node number   "  << i <<std::endl;
	    cn->setKD(lockd);
//	    std::cout << "line 150: lithology" << std::endl;
	    // NEED TO SET KB NEXT
//	    cn->setLayerErody(i, lockb);
    int node_id = cn->getPermID();
//    std::cout << "216" << "\n";
//	       	  	    std::cout << lockb << "\n";

     erody[i]=lockb;

}




   	  
   	   tLNode * cn;
  tMesh<tLNode>::nodeListIter_t ni( meshPtr->getNodeList() );
  
  for( cn = ni.FirstP(); ni.IsActive(); cn = ni.NextP() )
  {
    int node_id = cn->getID();
          std::cout << "  node id " << node_id << std:: endl;

    double local_erody = erody[node_id];
    std::cout << "There are " << cn->getNumLayer() << " layers at node " << node_id << std::endl;
    for( int i=0; i<cn->getNumLayer(); i++ )
    {
      std::cout << "  Working on layer " << i << std:: endl;
      if( cn->getLayerSed(i)==tLayer::kBedRock )
        cn->setLayerErody(i, local_erody);
    }
  }



//
//
//   	  // update Erody values at each node   	  
//
//	
//	for( int j=0; j<nnodes; j++)
//  {
//  	tLNode *cn;
//    cn = RNode[j];
////    int node_id = cn->getPermID();
//    double local_erody = erody[j];
////    std::cout << "There are " << cn->getNumLayer() << " layers at node " << node_id << std::endl;
//    for( int i=0; i<cn->getNumLayer(); i++ )
//    {
////      std::cout << "  Working on layer " << i << std:: endl;
//      if( cn->getLayerSed(i)==tLayer::kBedRock )
//        cn->setLayerErody(i, local_erody);
//    }
//    
//  }
//


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

void tLithology::UpdateLithology( tMesh<class tLNode> *mp, double delt)
{
	// if(1) std::cout << "Greetings from Update Lithology" << std::endl;
	
	//First update contact depths
	const int nnodes = mp->getNodeList()->getSize();  // # of nodes on list
    mp->RenumberIDCanonically();
    const tMesh< tLNode >::tIdArrayNode_t  RNode(*(mp->getNodeList()));
    double locuplift;
    double contactdepth; 
    double locnextdepth;
    double locz; 
    int locindex;
    int newunit;
    double nextdepth;
    double locerody;
    double lockd;
    double lockb;
      erody.setSize( nnodes );

	for( int i=0; i<nnodes; i++ )
   	  {
   	  	tLNode *cn;
   	  //	    std::cout << "264" << "\n";

        cn = RNode[i];
	     locuplift = cn->getUplift();	
	     locnextdepth = cn->getNextContactDepth();
	     locnextdepth = locnextdepth + (locuplift * delt);
	     cn->setNextContactDepth(locnextdepth);
//	     std::cout << "NextContactDepth value = " << locnextdepth << "  Delta t  " << delt << std::endl;

	     locz = cn->getZ();
//	     int node_id = cn->getPermID();

	     locerody = cn->getLayerErody(0);
	     erody[i]=locerody;
//	      std::cout << "erody" << erody[i] << "\n";

	     // update all the rest of the lower units
		for( int j=0; j<numlithounits-1; j++)
		{
		   contactdepth = cn->getLithoContactDepths(j);	
		   cn->setLithoContactDepths(j, contactdepth + locuplift);
		}
	
	    // check if local z is less than next contact, if so, update node properties
	    if( locz <= locnextdepth)
	    {
	    locindex = cn->getCurrentLithoIndex();
	    locindex++;
	    newunit = cn->getLithoUnitList(locindex);
	    nextdepth = cn->getLithoContactDepths(locindex);
	    
	    
	    // new unit is the code for the KD look up table as to which rock unit you are now in.  This is different than the local 'index' which is essentially tracking how many different layers you have eroded through. 
	    lockd = KDLookupTable[newunit];
	    
	    cn->setKD(lockd);
	       	  	//    std::cout << lockd << "\n";

	    lockb = KBLookupTable[newunit];
	    
//	   cn->setLayerErody(i, lockb);
	    	 
             erody[i]=lockb;
             std::cout << lockb << " " << i << " " << erody[i] <<"\n";
	    	// set new local values
	    	cn->setCurrentLithoIndex(locindex);
	    	cn->setNextContactDepth(nextdepth);
	    	cn->setCurrentLithoUnit(newunit);	    	
	    }
	
	
	
	
   	  }	
   	  
  // NEED TO MAKE SURE UPLIFT DURATION PARAMETER IS PROPERLY SET BECAUSE IF UPLIFT STOPS, 
  // LITHOLOGY WILL STILL THINK IT'S ONGOING, THINK ABOUT HOW TO FIX THIS 	  
   	  
   	   tLNode * cn;
  tMesh<tLNode>::nodeListIter_t ni( mp->getNodeList() );
  
  for( cn = ni.FirstP(); ni.IsActive(); cn = ni.NextP() )
  {
    int node_id = cn->getID();
    double local_erody = erody[node_id];
//    std::cout << "There are " << cn->getNumLayer() << " layers at node " << node_id << std::endl;
    for( int i=0; i<cn->getNumLayer(); i++ )
    {
//      std::cout << "  Working on layer " << i << std:: endl;
      if( cn->getLayerSed(i)==tLayer::kBedRock )
        cn->setLayerErody(i, local_erody);
    }
  }
    

   	  
 
//   	  working for spatial 
//   	  // update Erody values at each node   	  
//for( int j=0; j<nnodes; j++)
//  {
//  	tLNode *cn;
//    cn = RNode[j];
////    int node_id = cn->getPermID();
//    double local_erody = erody[j];
////    std::cout << "There are " << cn->getNumLayer() << " layers at node " << node_id << std::endl;
//    for( int i=0; i<cn->getNumLayer(); i++ )
//    {
////      std::cout << "  Working on layer " << i << std:: endl;
//      if( cn->getLayerSed(i)==tLayer::kBedRock )
//        {
//        cn->setLayerErody(i, local_erody);
//        std::cout << i << "\n";
//        }
//    }
//  }

	
	
	
}


