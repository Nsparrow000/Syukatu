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
 234;
 5.11416;-0.92735;-2.29620;,
 5.11416;32.00590;0.00000;,
 6.73782;-0.92735;-1.62366;,
 5.11416;32.00590;0.00000;,
 7.41037;-0.92735;0.00000;,
 5.11416;32.00590;0.00000;,
 6.73782;-0.92735;1.62366;,
 5.11416;32.00590;0.00000;,
 5.11416;-0.92735;2.29620;,
 5.11416;32.00590;0.00000;,
 3.49051;-0.92735;1.62366;,
 5.11416;32.00590;0.00000;,
 2.81796;-0.92735;-0.00000;,
 5.11416;32.00590;0.00000;,
 3.49051;-0.92735;-1.62366;,
 5.11416;32.00590;0.00000;,
 5.11416;-0.92735;-2.29620;,
 5.11416;-0.92735;-0.00000;,
 5.11416;-0.92735;-2.29620;,
 6.73782;-0.92735;-1.62366;,
 7.41037;-0.92735;0.00000;,
 6.73782;-0.92735;1.62366;,
 5.11416;-0.92735;2.29620;,
 3.49051;-0.92735;1.62366;,
 2.81796;-0.92735;-0.00000;,
 3.49051;-0.92735;-1.62366;,
 7.70523;-0.92735;-2.29620;,
 7.70523;32.00590;0.00000;,
 9.32888;-0.92735;-1.62366;,
 7.70523;32.00590;0.00000;,
 10.00140;-0.92735;0.00000;,
 7.70523;32.00590;0.00000;,
 9.32888;-0.92735;1.62366;,
 7.70523;32.00590;0.00000;,
 7.70523;-0.92735;2.29620;,
 7.70523;32.00590;0.00000;,
 6.08156;-0.92735;1.62366;,
 7.70523;32.00590;0.00000;,
 5.40903;-0.92735;-0.00000;,
 7.70523;32.00590;0.00000;,
 6.08156;-0.92735;-1.62366;,
 7.70523;32.00590;0.00000;,
 7.70523;-0.92735;-2.29620;,
 7.70523;-0.92735;-0.00000;,
 7.70523;-0.92735;-2.29620;,
 9.32888;-0.92735;-1.62366;,
 10.00140;-0.92735;0.00000;,
 9.32888;-0.92735;1.62366;,
 7.70523;-0.92735;2.29620;,
 6.08156;-0.92735;1.62366;,
 5.40903;-0.92735;-0.00000;,
 6.08156;-0.92735;-1.62366;,
 10.18745;-0.92735;-2.29620;,
 10.18745;32.00590;0.00000;,
 11.81109;-0.92735;-1.62366;,
 10.18745;32.00590;0.00000;,
 12.48363;-0.92735;0.00000;,
 10.18745;32.00590;0.00000;,
 11.81109;-0.92735;1.62366;,
 10.18745;32.00590;0.00000;,
 10.18745;-0.92735;2.29620;,
 10.18745;32.00590;0.00000;,
 8.56381;-0.92735;1.62366;,
 10.18745;32.00590;0.00000;,
 7.89125;-0.92735;-0.00000;,
 10.18745;32.00590;0.00000;,
 8.56381;-0.92735;-1.62366;,
 10.18745;32.00590;0.00000;,
 10.18745;-0.92735;-2.29620;,
 10.18745;-0.92735;-0.00000;,
 10.18745;-0.92735;-2.29620;,
 11.81109;-0.92735;-1.62366;,
 12.48363;-0.92735;0.00000;,
 11.81109;-0.92735;1.62366;,
 10.18745;-0.92735;2.29620;,
 8.56381;-0.92735;1.62366;,
 7.89125;-0.92735;-0.00000;,
 8.56381;-0.92735;-1.62366;,
 -2.31970;-0.92735;-2.29620;,
 -2.31970;32.00590;0.00000;,
 -0.69604;-0.92735;-1.62366;,
 -2.31970;32.00590;0.00000;,
 -0.02350;-0.92735;0.00000;,
 -2.31970;32.00590;0.00000;,
 -0.69604;-0.92735;1.62366;,
 -2.31970;32.00590;0.00000;,
 -2.31970;-0.92735;2.29620;,
 -2.31970;32.00590;0.00000;,
 -3.94336;-0.92735;1.62366;,
 -2.31970;32.00590;0.00000;,
 -4.61590;-0.92735;-0.00000;,
 -2.31970;32.00590;0.00000;,
 -3.94336;-0.92735;-1.62366;,
 -2.31970;32.00590;0.00000;,
 -2.31970;-0.92735;-2.29620;,
 -2.31970;-0.92735;0.00000;,
 -2.31970;-0.92735;-2.29620;,
 -0.69604;-0.92735;-1.62366;,
 -0.02350;-0.92735;0.00000;,
 -0.69604;-0.92735;1.62366;,
 -2.31970;-0.92735;2.29620;,
 -3.94336;-0.92735;1.62366;,
 -4.61590;-0.92735;-0.00000;,
 -3.94336;-0.92735;-1.62366;,
 0.27135;-0.92735;-2.29620;,
 0.27135;32.00590;0.00000;,
 1.89501;-0.92735;-1.62366;,
 0.27135;32.00590;0.00000;,
 2.56755;-0.92735;0.00000;,
 0.27135;32.00590;0.00000;,
 1.89501;-0.92735;1.62366;,
 0.27135;32.00590;0.00000;,
 0.27135;-0.92735;2.29620;,
 0.27135;32.00590;0.00000;,
 -1.35231;-0.92735;1.62366;,
 0.27135;32.00590;0.00000;,
 -2.02485;-0.92735;-0.00000;,
 0.27135;32.00590;0.00000;,
 -1.35231;-0.92735;-1.62366;,
 0.27135;32.00590;0.00000;,
 0.27135;-0.92735;-2.29620;,
 0.27135;-0.92735;-0.00000;,
 0.27135;-0.92735;-2.29620;,
 1.89501;-0.92735;-1.62366;,
 2.56755;-0.92735;0.00000;,
 1.89501;-0.92735;1.62366;,
 0.27135;-0.92735;2.29620;,
 -1.35231;-0.92735;1.62366;,
 -2.02485;-0.92735;-0.00000;,
 -1.35231;-0.92735;-1.62366;,
 2.75358;-0.92735;-2.29620;,
 2.75358;32.00590;0.00000;,
 4.37724;-0.92735;-1.62366;,
 2.75358;32.00590;0.00000;,
 5.04980;-0.92735;0.00000;,
 2.75358;32.00590;0.00000;,
 4.37724;-0.92735;1.62366;,
 2.75358;32.00590;0.00000;,
 2.75358;-0.92735;2.29620;,
 2.75358;32.00590;0.00000;,
 1.12993;-0.92735;1.62366;,
 2.75358;32.00590;0.00000;,
 0.45738;-0.92735;-0.00000;,
 2.75358;32.00590;0.00000;,
 1.12993;-0.92735;-1.62366;,
 2.75358;32.00590;0.00000;,
 2.75358;-0.92735;-2.29620;,
 2.75358;-0.92735;-0.00000;,
 2.75358;-0.92735;-2.29620;,
 4.37724;-0.92735;-1.62366;,
 5.04980;-0.92735;0.00000;,
 4.37724;-0.92735;1.62366;,
 2.75358;-0.92735;2.29620;,
 1.12993;-0.92735;1.62366;,
 0.45738;-0.92735;-0.00000;,
 1.12993;-0.92735;-1.62366;,
 -4.90850;-0.92735;-2.29620;,
 -4.90850;32.00590;0.00000;,
 -3.28484;-0.92735;-1.62366;,
 -4.90850;32.00590;0.00000;,
 -2.61230;-0.92735;0.00000;,
 -4.90850;32.00590;0.00000;,
 -3.28484;-0.92735;1.62366;,
 -4.90850;32.00590;0.00000;,
 -4.90850;-0.92735;2.29620;,
 -4.90850;32.00590;0.00000;,
 -6.53216;-0.92735;1.62366;,
 -4.90850;32.00590;0.00000;,
 -7.20470;-0.92735;-0.00000;,
 -4.90850;32.00590;0.00000;,
 -6.53216;-0.92735;-1.62366;,
 -4.90850;32.00590;0.00000;,
 -4.90850;-0.92735;-2.29620;,
 -4.90850;-0.92735;0.00000;,
 -4.90850;-0.92735;-2.29620;,
 -3.28484;-0.92735;-1.62366;,
 -2.61230;-0.92735;0.00000;,
 -3.28484;-0.92735;1.62366;,
 -4.90850;-0.92735;2.29620;,
 -6.53216;-0.92735;1.62366;,
 -7.20470;-0.92735;-0.00000;,
 -6.53216;-0.92735;-1.62366;,
 -7.39073;-0.92735;-2.29620;,
 -7.39073;32.00590;0.00000;,
 -5.76708;-0.92735;-1.62366;,
 -7.39073;32.00590;0.00000;,
 -5.09454;-0.92735;0.00000;,
 -7.39073;32.00590;0.00000;,
 -5.76708;-0.92735;1.62366;,
 -7.39073;32.00590;0.00000;,
 -7.39073;-0.92735;2.29620;,
 -7.39073;32.00590;0.00000;,
 -9.01440;-0.92735;1.62366;,
 -7.39073;32.00590;0.00000;,
 -9.68694;-0.92735;-0.00000;,
 -7.39073;32.00590;0.00000;,
 -9.01440;-0.92735;-1.62366;,
 -7.39073;32.00590;0.00000;,
 -7.39073;-0.92735;-2.29620;,
 -7.39073;-0.92735;0.00000;,
 -7.39073;-0.92735;-2.29620;,
 -5.76708;-0.92735;-1.62366;,
 -5.09454;-0.92735;0.00000;,
 -5.76708;-0.92735;1.62366;,
 -7.39073;-0.92735;2.29620;,
 -9.01440;-0.92735;1.62366;,
 -9.68694;-0.92735;-0.00000;,
 -9.01440;-0.92735;-1.62366;,
 -9.98178;-0.92735;-2.29620;,
 -9.98178;32.00590;0.00000;,
 -8.35814;-0.92735;-1.62366;,
 -9.98178;32.00590;0.00000;,
 -7.68559;-0.92735;0.00000;,
 -9.98178;32.00590;0.00000;,
 -8.35814;-0.92735;1.62366;,
 -9.98178;32.00590;0.00000;,
 -9.98178;-0.92735;2.29620;,
 -9.98178;32.00590;0.00000;,
 -11.60545;-0.92735;1.62366;,
 -9.98178;32.00590;0.00000;,
 -12.27798;-0.92735;-0.00000;,
 -9.98178;32.00590;0.00000;,
 -11.60544;-0.92735;-1.62366;,
 -9.98178;32.00590;0.00000;,
 -9.98178;-0.92735;-2.29620;,
 -9.98178;-0.92735;0.00000;,
 -9.98178;-0.92735;-2.29620;,
 -8.35814;-0.92735;-1.62366;,
 -7.68559;-0.92735;0.00000;,
 -8.35814;-0.92735;1.62366;,
 -9.98178;-0.92735;2.29620;,
 -11.60545;-0.92735;1.62366;,
 -12.27798;-0.92735;-0.00000;,
 -11.60544;-0.92735;-1.62366;;
 
 144;
 3;0,1,2;,
 3;2,3,4;,
 3;4,5,6;,
 3;6,7,8;,
 3;8,9,10;,
 3;10,11,12;,
 3;12,13,14;,
 3;14,15,16;,
 3;17,18,19;,
 3;17,19,20;,
 3;17,20,21;,
 3;17,21,22;,
 3;17,22,23;,
 3;17,23,24;,
 3;17,24,25;,
 3;17,25,18;,
 3;26,27,28;,
 3;28,29,30;,
 3;30,31,32;,
 3;32,33,34;,
 3;34,35,36;,
 3;36,37,38;,
 3;38,39,40;,
 3;40,41,42;,
 3;43,44,45;,
 3;43,45,46;,
 3;43,46,47;,
 3;43,47,48;,
 3;43,48,49;,
 3;43,49,50;,
 3;43,50,51;,
 3;43,51,44;,
 3;52,53,54;,
 3;54,55,56;,
 3;56,57,58;,
 3;58,59,60;,
 3;60,61,62;,
 3;62,63,64;,
 3;64,65,66;,
 3;66,67,68;,
 3;69,70,71;,
 3;69,71,72;,
 3;69,72,73;,
 3;69,73,74;,
 3;69,74,75;,
 3;69,75,76;,
 3;69,76,77;,
 3;69,77,70;,
 3;78,79,80;,
 3;80,81,82;,
 3;82,83,84;,
 3;84,85,86;,
 3;86,87,88;,
 3;88,89,90;,
 3;90,91,92;,
 3;92,93,94;,
 3;95,96,97;,
 3;95,97,98;,
 3;95,98,99;,
 3;95,99,100;,
 3;95,100,101;,
 3;95,101,102;,
 3;95,102,103;,
 3;95,103,96;,
 3;104,105,106;,
 3;106,107,108;,
 3;108,109,110;,
 3;110,111,112;,
 3;112,113,114;,
 3;114,115,116;,
 3;116,117,118;,
 3;118,119,120;,
 3;121,122,123;,
 3;121,123,124;,
 3;121,124,125;,
 3;121,125,126;,
 3;121,126,127;,
 3;121,127,128;,
 3;121,128,129;,
 3;121,129,122;,
 3;130,131,132;,
 3;132,133,134;,
 3;134,135,136;,
 3;136,137,138;,
 3;138,139,140;,
 3;140,141,142;,
 3;142,143,144;,
 3;144,145,146;,
 3;147,148,149;,
 3;147,149,150;,
 3;147,150,151;,
 3;147,151,152;,
 3;147,152,153;,
 3;147,153,154;,
 3;147,154,155;,
 3;147,155,148;,
 3;156,157,158;,
 3;158,159,160;,
 3;160,161,162;,
 3;162,163,164;,
 3;164,165,166;,
 3;166,167,168;,
 3;168,169,170;,
 3;170,171,172;,
 3;173,174,175;,
 3;173,175,176;,
 3;173,176,177;,
 3;173,177,178;,
 3;173,178,179;,
 3;173,179,180;,
 3;173,180,181;,
 3;173,181,174;,
 3;182,183,184;,
 3;184,185,186;,
 3;186,187,188;,
 3;188,189,190;,
 3;190,191,192;,
 3;192,193,194;,
 3;194,195,196;,
 3;196,197,198;,
 3;199,200,201;,
 3;199,201,202;,
 3;199,202,203;,
 3;199,203,204;,
 3;199,204,205;,
 3;199,205,206;,
 3;199,206,207;,
 3;199,207,200;,
 3;208,209,210;,
 3;210,211,212;,
 3;212,213,214;,
 3;214,215,216;,
 3;216,217,218;,
 3;218,219,220;,
 3;220,221,222;,
 3;222,223,224;,
 3;225,226,227;,
 3;225,227,228;,
 3;225,228,229;,
 3;225,229,230;,
 3;225,230,231;,
 3;225,231,232;,
 3;225,232,233;,
 3;225,233,226;;
 
 MeshMaterialList {
  1;
  144;
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
   0.000000;0.800000;0.128627;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.300000;0.048235;;
   TextureFilename {
    "af18.jpg";
   }
  }
 }
 MeshNormals {
  73;
  -0.000000;0.069554;-0.997578;,
  0.705392;0.069554;-0.705396;,
  0.997578;0.069554;0.000000;,
  0.705392;0.069554;0.705396;,
  -0.000000;0.069554;0.997578;,
  -0.705395;0.069554;0.705394;,
  -0.997578;0.069554;0.000000;,
  -0.705395;0.069554;-0.705394;,
  0.000000;-1.000000;-0.000000;,
  0.000002;0.069554;-0.997578;,
  0.705398;0.069554;-0.705390;,
  0.997578;0.069553;0.000000;,
  0.705398;0.069554;0.705390;,
  0.000002;0.069554;0.997578;,
  -0.705395;0.069554;0.705393;,
  -0.997578;0.069554;0.000000;,
  -0.705395;0.069554;-0.705393;,
  0.000000;0.069554;-0.997578;,
  0.705395;0.069554;-0.705393;,
  0.997578;0.069553;0.000000;,
  0.705395;0.069554;0.705393;,
  0.000000;0.069554;0.997578;,
  -0.705393;0.069554;0.705396;,
  -0.997578;0.069554;0.000000;,
  -0.705393;0.069554;-0.705396;,
  0.000000;0.069554;-0.997578;,
  0.705394;0.069554;-0.705394;,
  0.997578;0.069554;0.000000;,
  0.705394;0.069554;0.705394;,
  -0.000000;0.069554;0.997578;,
  -0.705395;0.069554;0.705393;,
  -0.997578;0.069554;0.000000;,
  -0.705395;0.069554;-0.705393;,
  0.000000;0.069554;-0.997578;,
  0.705396;0.069554;-0.705393;,
  0.997578;0.069554;0.000000;,
  0.705396;0.069554;0.705393;,
  0.000000;0.069554;0.997578;,
  -0.705394;0.069554;0.705394;,
  -0.997578;0.069554;0.000000;,
  -0.705394;0.069554;-0.705394;,
  -0.000000;0.069554;-0.997578;,
  0.705391;0.069554;-0.705397;,
  0.997578;0.069555;0.000000;,
  0.705391;0.069554;0.705397;,
  -0.000001;0.069554;0.997578;,
  -0.705394;0.069554;0.705395;,
  -0.997578;0.069554;0.000000;,
  -0.705394;0.069554;-0.705395;,
  0.000000;0.069554;-0.997578;,
  0.705395;0.069554;-0.705394;,
  0.997578;0.069554;0.000000;,
  0.705395;0.069554;0.705394;,
  0.000000;0.069554;0.997578;,
  -0.705395;0.069554;0.705393;,
  -0.997578;0.069554;0.000000;,
  -0.705395;0.069554;-0.705393;,
  0.000002;0.069554;-0.997578;,
  0.705395;0.069554;-0.705394;,
  0.997578;0.069554;0.000000;,
  0.705395;0.069554;0.705394;,
  0.000002;0.069554;0.997578;,
  -0.705393;0.069554;0.705395;,
  -0.997578;0.069554;0.000000;,
  -0.705393;0.069554;-0.705396;,
  0.000002;0.069554;-0.997578;,
  0.705394;0.069554;-0.705395;,
  0.997578;0.069554;0.000000;,
  0.705394;0.069554;0.705395;,
  0.000003;0.069554;0.997578;,
  -0.705394;0.069554;0.705394;,
  -0.997578;0.069554;-0.000001;,
  -0.705394;0.069554;-0.705395;;
  144;
  3;0,1,1;,
  3;1,1,2;,
  3;2,3,3;,
  3;3,3,4;,
  3;4,5,5;,
  3;5,5,6;,
  3;6,7,7;,
  3;7,7,0;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;9,10,10;,
  3;10,10,11;,
  3;11,12,12;,
  3;12,12,13;,
  3;13,14,14;,
  3;14,14,15;,
  3;15,16,16;,
  3;16,16,9;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;17,18,18;,
  3;18,18,19;,
  3;19,20,20;,
  3;20,20,21;,
  3;21,22,22;,
  3;22,22,23;,
  3;23,24,24;,
  3;24,24,17;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;25,26,26;,
  3;26,26,27;,
  3;27,28,28;,
  3;28,28,29;,
  3;29,30,30;,
  3;30,30,31;,
  3;31,32,32;,
  3;32,32,25;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;33,34,34;,
  3;34,34,35;,
  3;35,36,36;,
  3;36,36,37;,
  3;37,38,38;,
  3;38,38,39;,
  3;39,40,40;,
  3;40,40,33;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;41,42,42;,
  3;42,42,43;,
  3;43,44,44;,
  3;44,44,45;,
  3;45,46,46;,
  3;46,46,47;,
  3;47,48,48;,
  3;48,48,41;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;49,50,50;,
  3;50,50,51;,
  3;51,52,52;,
  3;52,52,53;,
  3;53,54,54;,
  3;54,54,55;,
  3;55,56,56;,
  3;56,56,49;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;57,58,58;,
  3;58,58,59;,
  3;59,60,60;,
  3;60,60,61;,
  3;61,62,62;,
  3;62,62,63;,
  3;63,64,64;,
  3;64,64,57;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;65,66,66;,
  3;66,66,67;,
  3;67,68,68;,
  3;68,68,69;,
  3;69,70,70;,
  3;70,70,71;,
  3;71,72,72;,
  3;72,72,65;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;,
  3;8,8,8;;
 }
 MeshTextureCoords {
  234;
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
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
