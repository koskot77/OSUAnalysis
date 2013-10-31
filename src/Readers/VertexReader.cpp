/*
 * PrimaryVertexReader.cpp
 *
 *  Created on: 25 Jul 2010
 *      Author: kreczko
 */

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/Event.h"
 
#include "ProductArea/BNcollections/interface/BNprimaryvertex.h"


#include "../../interface/Readers/VertexReader.h"

namespace BAT {

VertexReader::VertexReader() :
	ndofReader(),
	zReader(),
	rhoReader(),
	isfakeReader(),
	vertices() {

}

VertexReader::VertexReader(TChainPointer input) :
	ndofReader(input, "goodOfflinePrimaryVertices.NDF"),
	zReader(input, "goodOfflinePrimaryVertices.Z"),
	rhoReader(input, "goodOfflinePrimaryVertices.Rho"),
	isfakeReader(input, "goodOfflinePrimaryVertices.IsFake"),
	vertices() {

}

void VertexReader::initialise() {
	/*
    ndofReader.initialise();
    zReader.initialise();
    rhoReader.initialise();
    isfakeReader.initialise();
    */
}

const VertexCollection& VertexReader::getVertices(
	const fwlite::ChainEvent *const evtchain) {
    if (vertices.empty() == false)
        vertices.clear();
    readVertices(evtchain);
    return vertices;
}

void VertexReader::readVertices(const fwlite::ChainEvent *const evtchain) {
		fwlite::Handle<BNprimaryvertexCollection> h_pvs;
		h_pvs.getByLabel(*evtchain,"BNproducer","offlinePrimaryVertices");
	for (unsigned int index = 0; index < h_pvs->size(); index++) {
		const BNprimaryvertex *const vertstruc = &h_pvs->at(index);
		VertexPointer vertex(new Vertex());
		vertex->setDegreesOfFreedom(vertstruc->ndof);
		vertex->setFake(vertstruc->isFake);
		vertex->setRho(vertstruc->rho);
		vertex->setZPosition(vertstruc->z);
		vertices.push_back(vertex);
    }
}

VertexReader::~VertexReader() {
}

}
