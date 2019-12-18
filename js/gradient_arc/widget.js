class GradientArc {
    constructor(assets, config) {
        this._rawAssets = assets;
        this._rawConfig = config;
        this._createComponent();
        this._addProgressCircle();
    }

    render(parentId) {
        let parent = document.getElementById(parentId);
        parent.appendChild(this.component);
    }

    _createComponent() {
        this.component = document.createElement("div");
        this.component.innerHTML =
            `<div id="component_container">
                <canvas id="arc_canvas"></canvas>
            </div>`;
        this.canvas = this.component.getElementsByTagName("canvas")[0];
        this.canvas.height = this._assets('canvasSizePx');
        this.canvas.width = this._assets('canvasSizePx');
    }

    _addProgressCircle() {
        let center = {
            x: this.canvas.height / 2,
            y: this.canvas.height / 2
        };
        let radius = this.canvas.width / 2 - this._assets('arcWidth') / 2;

        let startAngle = -Math.PI / 2;
        let arcsData = [];
        for(let i = 0; i < this._assets('colors').length; i++) {
            let endAngle = startAngle + 2 * Math.PI / this._assets('colors').length;
            arcsData.push({
                startAngle: startAngle,
                endAngle: endAngle,
                x1: center.x + radius * Math.cos(startAngle),
                y1: center.y + radius * Math.sin(startAngle),
                x2: center.x + radius * Math.cos(endAngle),
                y2: center.y + radius * Math.sin(endAngle),
                colors: [
                    {
                        stop: 0,
                        value: i < this._config("level", 0)
                               ? this._assets('colors')[i]
                               : this._assets('defaultColor')
                    },
                    {
                        stop: 1,
                        value: i < this._config("level", 0)
                               ? this._assets('colors')[(i + 1) % this._assets('colors').length]
                               : this._assets('defaultColor')
                    }
                ]
            })
            startAngle = endAngle;
        }

        let ctx = this.canvas.getContext("2d");
        for(let arc of arcsData) {
            let gradient = ctx.createLinearGradient(arc.x1, arc.y1, arc.x2, arc.y2);
            for(let color of arc.colors)
                gradient.addColorStop(color.stop, color.value);

            ctx.beginPath();
            ctx.arc(center.x, center.y, radius, arc.startAngle, arc.endAngle);
            ctx.strokeStyle = gradient;
            ctx.lineWidth = this._assets('arcWidth');
            ctx.stroke();
        }
    }

    _config(propertyName, defaultValue = '') {
        if(!(propertyName in this._rawConfig)) {
            console.log(`Config property "${propertyName}" not specified. Using "${defaultValue}" as default value.`);
            return defaultValue;
        }
        return this._rawConfig[propertyName];
    }

    _assets(assetName) {
        if(!(assetName in this._rawAssets))
            throw `Asset "${assetName}" not specified. All assets are mandatory.`;
        return this._rawAssets[assetName];
    }
}
