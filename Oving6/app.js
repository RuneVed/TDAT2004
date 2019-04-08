



let ws = new WebSocket('ws://localhost:3210',['json', 'xml']);
//ws.onmessage = e => console.log(e.data + "haha");
ws.addEventListener('open', () => {
    let data = { message: 'Hei hei' };
    let json = JSON.stringify(data);
    ws.send(json);
});
ws.addEventListener('message', event => {
    const data = JSON.parse(event.data);
    console.log(data);
});