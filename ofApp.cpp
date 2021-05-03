#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	int v_span = 1;
	int u_span = 60;

	float z = 360 * -2;
	float z_span = 1;
	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	for (int v = 0; v <= 360 * 4; v += v_span) {

		bool flag = true;
		int u_start = ofMap(ofNoise(z * 0.005 + ofGetFrameNum() * 0.015), 0, 1, -720, 720);
		int next_u = ofMap(ofNoise((z + z_span) * 0.005 + ofGetFrameNum() * 0.015), 0, 1, -720, 720);
		for (int u = u_start; u < u_start + 360; u += u_span) {

			if (flag) {

				face.addVertex(this->make_point(200, 50, u, v) + glm::vec3(0, 0, z));
				face.addVertex(this->make_point(200, 50, u + u_span, v) + glm::vec3(0, 0, z));
				face.addVertex(this->make_point(200, 50, next_u + u_span, v + v_span) + glm::vec3(0, 0, z + z_span));
				face.addVertex(this->make_point(200, 50, next_u, v + v_span) + glm::vec3(0, 0, z + z_span));

				line.addVertex(this->make_point(200, 50, u, v) + glm::vec3(0, 0, z));
				line.addVertex(this->make_point(200, 50, u + u_span, v) + glm::vec3(0, 0, z));
				line.addVertex(this->make_point(200, 50, next_u + u_span, v + v_span) + glm::vec3(0, 0, z + z_span));
				line.addVertex(this->make_point(200, 50, next_u, v + v_span) + glm::vec3(0, 0, z + z_span));

				ofColor color;
				color.setHsb(ofMap(u, u_start, u_start + 360, 0, 255), 150, 255);

				face.addColor(color);
				face.addColor(color);
				face.addColor(color);
				face.addColor(color);

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
			}

			next_u += u_span;
			flag = !flag;
		}

		z += z_span;
	}

	face.drawFaces();

	ofSetColor(39);
	line.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// ���w�f�b�T������ �`���Ċy���ސ��w�����@P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}