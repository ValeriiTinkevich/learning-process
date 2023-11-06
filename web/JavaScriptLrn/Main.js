const readline = require('readline').createInterface({

    input: process.stdin,
    
    output: process.stdout
    
    });
    
    readline.question('Как вас зовут?', name => {
    
    console.log(name);
    
    readline.close();
    
    });