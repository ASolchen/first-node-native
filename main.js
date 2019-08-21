//https://blog.risingstack.com/writing-native-node-js-modules/
//npm install node-gyp
//node-gyp configure
//node-gyp build
const myAddon = require('./build/Release/addon')
const t = Date.now()
let num= 0.0;
if(false){
  const rando = [1000.0, 2.0, 3.4, 7.0, 50.0]
  for(let i=0;i<100000;i++){
    num += rando[i%5];
  } 
}
else{
  num = myAddon.myarray()
}

console.log(num)
console.log(0.001 *(Date.now() - t))