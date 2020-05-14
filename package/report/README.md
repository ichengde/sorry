# error catch

## usage
```javascript
    
    import { sorry, errorHandler } from 'chegde-sorry';
    
    sorry.config({
    project: '',
    id: '',
    version: process.env.VERSION,
    reportUrl: '',
    });


    window.addEventListener('error', errorHandler) // not necessary

```

### description
when it throws error then it uploads these infos:
1. watch console event
2. watch document click event
3. watch hash change event

