#define AA 2

// Blue Smoke Ring
// #define t iTime
// mat2 m(float a){float c=cos(a), s=sin(a);return mat2(c,-s,s,c);}
// float map(vec3 p){
//     p.xz*= m(t*0.4);p.xy*= m(t*0.3);
//     vec3 q = p*1.+t;
//     return length(p+vec3(sin(t*0.7)))*log(length(p)+1.) + sin(q.x+sin(q.z+sin(q.y)))*0.5 - 1.;
// }

// void mainImage( out vec4 fragColor, in vec2 fragCoord ){  
//   vec2 p = fragCoord.xy/iResolution.y - vec2(.9,.5);
//     vec3 cl = vec3(0.);
//     float d = 2.5;
//     for(int i=0; i<=5; i++) {
//     vec3 p = vec3(0,0,5.) + normalize(vec3(p, -1.))*d;
//         float rz = map(p);
//     float f =  clamp((rz - map(p+.1))*0.5, -.1, 1. );
//         vec3 l = vec3(0.1,0.3,.4) + vec3(5., 2.5, 3.)*f;
//         cl = cl*l + (1.-smoothstep(0., 2.5, rz))*.7*l;
//     d += min(rz, 1.);
//   }
//     fragColor = vec4(cl, 1.);
// }

// Colorful bubbles -- LED Optimized
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
  vec2 uv = -1.0 + 0.5*fragCoord.xy / iResolution.xy;
  uv.x *=  iResolution.x / iResolution.y;

    // background  
  vec3 color = vec3(0.8 + 0.2*uv.y);

    // bubbles  
  for( int i=0; i<100; i++ )
  {
        // bubble seeds
    float pha =      sin(float(i)*546.13+1.0)*0.5 + 0.5;
    float siz = pow( sin(float(i)*651.74+5.0)*0.5 + 0.5, 4.0 );
    float pox =      sin(float(i)*321.55+4.1) * iResolution.x / iResolution.y;

    // buble size, position and color
    float rad = 0.1*aPower + 0.5*siz;
    vec2  pos = vec2( pox, -1.0-rad + (2.0+2.0*rad)*mod(pha+0.1*iTime*(0.2+0.8*siz),1.0));
    float dis = length( uv - pos );
    vec3  col = mix( vec3(0.94,0.3,0.0), vec3(0.2,0.4,0.8), 0.5+0.5*sin(float(i)*1.2+1.9));
       // col+= 8.0*smoothstep( rad*0.95, rad, dis );
    
    // render
    float f = length(uv-pos)/rad;
    f = sqrt(clamp(1.0-f*f,0.0,1.0));
    color -= col.zyx *(1.0-smoothstep( rad*0.95, rad, dis )) * f;
  }

    // vigneting  
  color *= sqrt(1.5-0.5*length(uv));

  fragColor = vec4(color, aAlpha);
}


// PRISM -- LED Optimized
// #define t iTime
// #define r iResolution.xy

// void mainImage( out vec4 fragColor, in vec2 fragCoord ){
//   vec3 c;
//   float l,z=t;
//   for (int i=0;i<3;i++) {
//     vec2 uv,p=fragCoord.xy/r;
//     uv=p;
//     p-=.5;
//     p.x*=r.x/r.y;
//     z+=.07;
//     l=length(p);
//     uv+=p/l*(sin(z*0.2)+0.2)*abs(sin(l*1.-z*1.));
//     c[i]=.01/length(abs(mod(uv,1.)-.5));
//   }
//   fragColor=vec4(c/l,t);
// }
