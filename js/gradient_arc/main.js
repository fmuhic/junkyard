let config = {
    level: 4,
};

let assets = {
    colors: [
        '#FF0000',
        '#FF6400',
        '#FF9B46',
        '#FCCC02',
        '#ABB335',
        '#65B761'
    ],
    defaultColor: '#D6DBDF',
    arcWidth: 10,
    canvasSizePx: 180
};

let parentId = 'gradient_arc_widget';
let widget = new GradientArc(assets, config);
widget.render(parentId);
