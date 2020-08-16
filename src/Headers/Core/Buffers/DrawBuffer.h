#ifndef Draw_BUFFER_H
#define Draw_BUFFER_H


class DrawBuffer {
private:
	VertexArray va;
	VertexBuffer<float> vb;
	VertexBuffer<unsigned int> eb;
	unsigned int w = 1;
	std::vector <Drawable*> drawbuf;
	std::vector<float> wb;
	unsigned int drawbs_c = 0;
public :

	DrawBuffer();
	~DrawBuffer();

	void delDraw(unsigned int);

	void addDrawable(Drawable*);
	void updDrawable(unsigned int);
	void Done();
	void vDone();
	void eDone();
	void WireFrameMode(bool = true);
	void Draw();

	void vPrint();
	void ePrint();

	unsigned int getCount();
};

DrawBuffer::DrawBuffer() : va(VertexArray()), vb(VertexBuffer<float>()), eb(VertexBuffer<unsigned int>(GL_ELEMENT_ARRAY_BUFFER)) {
	vb.VertexAttrib(4, 3, 4, 2, 1);
	w = vb.getW();
	wb.resize(w);
}
void DrawBuffer::addDrawable(Drawable* drawable) {
	drawable->id = drawbs_c;
	VertexData* vertexdata = drawable->getVertexDataPtr();
	for (unsigned int i = 0; i < drawable->getVertexCount(); i++) {
		VertexData curr = vertexdata[i];
		float* arr = curr.getPtr();
		for (unsigned int j = 0; j < w; j++)
			wb[j] = arr[j];
		vb.addVertex(wb);
	}
	
	unsigned int aibs = drawable->getAIBSize();
	unsigned int ribs = drawable->getRIBSize();
	if (aibs) {
		unsigned int* paib = drawable->getAIBPtr();
		for (unsigned int i = 0; i < aibs;i++)
			eb.addVertex({ paib[i]});
	}
	if (ribs) {
		unsigned int pvc = 0;
		for (unsigned int i = 0; i < drawbs_c; i++) {
		pvc += drawbuf[i]->getVertexCount();
		}
		unsigned int* prib = drawable->getRIBPtr();
		for (unsigned int i = 0; i < ribs;i++) {
			eb.addVertex({pvc  + prib[i] });
		}
	}
	drawbuf.push_back(drawable);
	drawbs_c++;
}

void DrawBuffer::updDrawable(unsigned int id) {
	VertexData* vd = drawbuf[id]->getVertexDataPtr();
	unsigned int vc = drawbuf[id]->getVertexCount();
	unsigned int pvc = 0;
	for (unsigned int i = 0; i < id; i++)
		pvc += drawbuf[i]->getVertexCount();
	for (unsigned int i = 0; i < vc; i++) {
		float* arr = vd[i].getPtr();
		for (unsigned int j = 0; j < w; j++)
			wb[j] = arr[j];
		vb.updVertex(pvc + i, wb);
		free(arr);
	}
	vb.updBufferV( pvc, vc);
}
void DrawBuffer::WireFrameMode(bool toggle) {
	VertexBuffer<float>::WireFrameMode(toggle);
}

void DrawBuffer::delDraw(unsigned int id) {
	vb.delVertex(id, drawbuf[id]->getVertexCount());
	eb.delVertex(id, drawbuf[id]->getRIBSize());
}

void DrawBuffer::Done() {
	vb.Done();eb.Done();
}
void DrawBuffer::vDone() {
	vb.Done();
}
void DrawBuffer::eDone() {
	eb.Done();
}
void DrawBuffer::vPrint() {
	vb.Print();
}
void DrawBuffer::ePrint() {
	eb.Print();
}


void DrawBuffer::Draw() {
	eb.Draw();
}
DrawBuffer::~DrawBuffer() {}

#endif
