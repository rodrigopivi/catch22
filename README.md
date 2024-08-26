<p align="center"><img src="img/catch22_logo_square.png" alt="catch22 logo" height="220"/></p>

<h1 align="center"><em>catch22</em>: CAnonical Time-series CHaracteristics (for NodeJS)</h1>


A fork of [_catch22_](https://github.com/DynamicsAndNeuralSystems/catch22) to support Nodejs. Just `npm i catch22` and you are ready.

### Example

```ts
const catch22 = require('catch22');

const data = [1,2,3,4,5,6,7,8,9,10];

const features22 = catch22.catch22(data);
const features24 = catch22.catch24(data);

const mode5 = catch22.DN_HistogramMode_5(data);

console.log('features22: ', features22);
console.log('features24: ', features24);
console.log('DN_HistogramMode_5: ', mode5);
```

For more information, check the official [&#x1F4D7;___catch22_ documentation__](https://time-series-features.gitbook.io/catch22/)
