xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 68;
 22.24851;2.93490;1.51500;,
 22.24851;2.47218;2.52939;,
 22.24851;0.97030;3.12258;,
 22.24851;0.97030;1.51500;,
 22.24852;0.97030;-3.11756;,
 22.24852;2.47218;-2.52437;,
 22.24852;2.93490;-1.50997;,
 22.24851;0.97030;-1.50997;,
 22.24851;-0.99429;3.12258;,
 22.24851;-0.99429;1.51500;,
 22.24852;-0.99429;-3.11756;,
 22.24851;-0.99429;-1.50997;,
 22.24851;-2.32383;2.60851;,
 22.24851;-2.95889;1.51500;,
 22.24851;-2.32383;-2.60349;,
 22.24851;-2.95889;-1.50999;,
 22.24851;3.24895;0.00251;,
 22.24851;0.97030;0.00251;,
 22.24851;-0.99429;0.00251;,
 22.24851;-3.11860;0.00251;,
 0.05890;-1.09909;3.44715;,
 0.05890;-1.09909;1.67232;,
 0.05890;-3.26805;1.67232;,
 0.05890;-2.56693;2.87959;,
 0.05890;-3.26805;-1.66735;,
 0.05890;-1.09909;-1.66735;,
 0.05891;-1.09909;-3.44218;,
 0.05890;-2.56693;-2.87462;,
 0.05890;1.06990;3.44715;,
 0.05890;1.06990;1.67232;,
 0.05891;1.06990;-3.44218;,
 0.05890;1.06990;-1.66735;,
 0.05890;2.72803;2.79224;,
 0.05890;3.23887;1.67232;,
 0.05891;2.72803;-2.78728;,
 0.05891;3.23887;-1.66735;,
 0.05890;-3.44438;0.00248;,
 0.05890;-1.09909;0.00248;,
 0.05890;1.06990;0.00248;,
 0.05890;3.58559;0.00248;,
 14.85197;-2.41809;2.71438;,
 14.85197;-3.07894;1.57644;,
 14.85198;-2.41809;-2.70938;,
 14.85198;-3.07894;-1.57144;,
 7.45543;-2.46495;2.76638;,
 7.45543;-3.13849;1.60662;,
 7.45544;-2.46495;-2.76140;,
 7.45544;-3.13849;-1.60164;,
 14.85197;-3.24515;0.00250;,
 7.45543;-3.30787;0.00249;,
 7.45544;2.62165;2.68247;,
 7.45544;3.11240;1.60662;,
 7.45545;2.62165;-2.67749;,
 7.45544;3.11240;-1.60164;,
 14.85198;2.57278;2.63205;,
 14.85197;3.05428;1.57644;,
 14.85198;2.57278;-2.62703;,
 14.85198;3.05428;-1.57144;,
 7.45544;3.44547;0.00249;,
 14.85197;3.38109;0.00250;,
 7.45543;-1.05486;3.31161;,
 7.45544;-1.05486;-3.30662;,
 14.85197;-1.03453;3.24933;,
 14.85198;-1.03453;-3.24433;,
 7.45543;1.02877;3.31161;,
 7.45544;1.02877;-3.30662;,
 14.85197;1.00987;3.24933;,
 14.85198;1.00987;-3.24433;;
 
 66;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;3,2,8,9;,
 4;10,4,7,11;,
 4;9,8,12,13;,
 4;14,10,11,15;,
 4;16,0,3,17;,
 4;7,6,16,17;,
 4;17,3,9,18;,
 4;11,7,17,18;,
 4;18,9,13,19;,
 4;15,11,18,19;,
 4;20,21,22,23;,
 4;24,25,26,27;,
 4;21,20,28,29;,
 4;30,26,25,31;,
 4;29,28,32,33;,
 4;34,30,31,35;,
 4;36,22,21,37;,
 4;25,24,36,37;,
 4;37,21,29,38;,
 4;31,25,37,38;,
 4;38,29,33,39;,
 4;35,31,38,39;,
 4;13,12,40,41;,
 4;42,14,15,43;,
 4;41,40,44,45;,
 4;46,42,43,47;,
 4;23,22,45,44;,
 4;47,24,27,46;,
 4;19,13,41,48;,
 4;43,15,19,48;,
 4;48,41,45,49;,
 4;47,43,48,49;,
 4;49,45,22,36;,
 4;24,47,49,36;,
 4;33,32,50,51;,
 4;52,34,35,53;,
 4;51,50,54,55;,
 4;56,52,53,57;,
 4;55,54,1,0;,
 4;5,56,57,6;,
 4;39,33,51,58;,
 4;53,35,39,58;,
 4;58,51,55,59;,
 4;57,53,58,59;,
 4;59,55,0,16;,
 4;6,57,59,16;,
 4;44,60,20,23;,
 4;26,61,46,27;,
 4;60,44,40,62;,
 4;42,46,61,63;,
 4;62,40,12,8;,
 4;14,42,63,10;,
 4;28,20,60,64;,
 4;61,26,30,65;,
 4;64,60,62,66;,
 4;63,61,65,67;,
 4;66,62,8,2;,
 4;10,63,67,4;,
 4;32,28,64,50;,
 4;65,30,34,52;,
 4;50,64,66,54;,
 4;67,65,52,56;,
 4;54,66,2,1;,
 4;4,67,56,5;;
 
 MeshMaterialList {
  1;
  66;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.640000;0.640000;0.640000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  78;
  -1.000000;0.000000;0.000000;,
  -1.000000;0.000003;-0.000003;,
  1.000000;0.000000;0.000000;,
  1.000000;-0.000002;0.000003;,
  -1.000000;0.000004;-0.000005;,
  1.000000;-0.000003;0.000004;,
  1.000000;-0.000001;0.000001;,
  -1.000000;0.000001;-0.000002;,
  1.000000;-0.000003;0.000003;,
  1.000000;-0.000001;0.000002;,
  -1.000000;0.000003;-0.000004;,
  -1.000000;0.000001;-0.000002;,
  1.000000;-0.000001;0.000004;,
  1.000000;-0.000002;0.000005;,
  -1.000000;0.000001;-0.000005;,
  -1.000000;0.000002;-0.000006;,
  1.000000;-0.000001;0.000003;,
  1.000000;-0.000001;0.000002;,
  1.000000;-0.000001;0.000001;,
  -1.000000;0.000001;-0.000003;,
  -1.000000;0.000002;-0.000004;,
  -1.000000;0.000001;-0.000001;,
  0.015025;-0.649331;0.760358;,
  0.015027;-0.649329;-0.760359;,
  0.014309;-0.649338;0.760366;,
  0.014311;-0.649336;-0.760367;,
  0.015077;0.688482;0.725097;,
  0.015079;0.688481;-0.725098;,
  0.014460;0.688487;0.725105;,
  0.014462;0.688487;-0.725105;,
  0.014162;-0.950492;0.310426;,
  0.014163;-0.950492;-0.310426;,
  0.013462;-0.950501;0.310430;,
  0.013463;-0.950501;-0.310430;,
  0.012793;-0.999918;-0.000000;,
  0.013466;-0.999909;0.000000;,
  0.013329;0.950296;0.311062;,
  0.013330;0.950296;-0.311063;,
  0.013873;0.950289;0.311059;,
  0.013874;0.950289;-0.311060;,
  0.013284;0.999912;-0.000000;,
  0.013822;0.999905;-0.000000;,
  0.013311;-0.183413;0.982946;,
  0.013313;-0.183412;-0.982946;,
  0.013944;-0.183412;0.982937;,
  0.013946;-0.183411;-0.982937;,
  0.013290;0.186955;0.982279;,
  0.013292;0.186956;-0.982278;,
  0.013893;0.186954;0.982270;,
  0.013896;0.186953;-0.982271;,
  0.018006;-0.950433;0.310408;,
  0.019156;-0.649284;0.760304;,
  0.019158;-0.649283;-0.760305;,
  0.018006;-0.950433;-0.310409;,
  0.020588;-0.649266;0.760283;,
  0.019406;-0.950409;0.310397;,
  0.019406;-0.950409;-0.310398;,
  0.020590;-0.649265;-0.760284;,
  0.017106;-0.999854;-0.000000;,
  0.018452;-0.999830;0.000000;,
  0.019010;0.950209;0.311033;,
  0.020660;0.688413;0.725024;,
  0.020661;0.688412;-0.725025;,
  0.019011;0.950209;-0.311033;,
  0.019425;0.688428;0.725044;,
  0.017921;0.950227;0.311041;,
  0.019427;0.688429;-0.725044;,
  0.017922;0.950227;-0.311042;,
  0.018940;0.999821;0.000000;,
  0.017863;0.999840;-0.000000;,
  0.019107;-0.183396;0.982853;,
  0.019109;-0.183395;-0.982853;,
  0.017841;-0.183400;0.982877;,
  0.017843;-0.183399;-0.982877;,
  0.019037;0.186937;0.982187;,
  0.019040;0.186936;-0.982188;,
  0.017832;0.186941;0.982209;,
  0.017834;0.186943;-0.982209;;
  66;
  4;2,2,2,2;,
  4;13,5,8,16;,
  4;2,2,2,2;,
  4;12,13,16,17;,
  4;2,2,2,2;,
  4;3,12,17,6;,
  4;9,2,2,18;,
  4;16,8,9,18;,
  4;18,2,2,2;,
  4;17,16,18,2;,
  4;2,2,2,2;,
  4;6,17,2,2;,
  4;0,0,0,0;,
  4;7,19,14,1;,
  4;0,0,0,0;,
  4;15,14,19,20;,
  4;0,0,0,0;,
  4;4,15,20,10;,
  4;0,0,0,0;,
  4;19,7,0,0;,
  4;0,0,0,21;,
  4;20,19,0,21;,
  4;21,0,0,11;,
  4;10,20,21,11;,
  4;50,51,24,32;,
  4;25,52,53,33;,
  4;32,24,22,30;,
  4;23,25,33,31;,
  4;54,55,30,22;,
  4;31,56,57,23;,
  4;58,50,32,34;,
  4;33,53,58,34;,
  4;34,32,30,35;,
  4;31,33,34,35;,
  4;35,30,55,59;,
  4;56,31,35,59;,
  4;60,61,26,38;,
  4;27,62,63,39;,
  4;38,26,28,36;,
  4;29,27,39,37;,
  4;36,28,64,65;,
  4;66,29,37,67;,
  4;68,60,38,41;,
  4;39,63,68,41;,
  4;41,38,36,40;,
  4;37,39,41,40;,
  4;40,36,65,69;,
  4;67,37,40,69;,
  4;22,44,70,54;,
  4;71,45,23,57;,
  4;44,22,24,42;,
  4;25,23,45,43;,
  4;42,24,51,72;,
  4;52,25,43,73;,
  4;74,70,44,48;,
  4;45,71,75,49;,
  4;48,44,42,46;,
  4;43,45,49,47;,
  4;46,42,72,76;,
  4;73,43,47,77;,
  4;61,74,48,26;,
  4;49,75,62,27;,
  4;26,48,46,28;,
  4;47,49,27,29;,
  4;28,46,76,64;,
  4;77,47,29,66;;
 }
 MeshTextureCoords {
  68;
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
