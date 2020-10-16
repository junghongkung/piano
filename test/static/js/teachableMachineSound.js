// https://github.com/tensorflow/tfjs-models/tree/master/speech-commands

//the link to your model provided by Teachable Machine export panel
const URL = "https://teachablemachine.withgoogle.com/models/S7Lp8U-en/";
var flag = true;  //플래그 설정. 웹소켓이 0.5초마다 무한연결되지 않도록한다(처음 한번만 연결됨)

async function createModel() {
    const checkpointURL = URL + "model.json"; // model topology
    const metadataURL = URL + "metadata.json"; // model metadata

    const recognizer = speechCommands.create(
        "BROWSER_FFT", // fourier transform type, not useful to change
        undefined, // speech commands vocabulary feature, not useful for your models
        checkpointURL,
        metadataURL);

    // check that model and metadata are loaded via HTTPS requests.
    await recognizer.ensureModelLoaded();

    //소켓 연결
    /*console.log(location.protocol)
    console.log(document.domain)
    console.log(location.port)*/
    socket = io.connect(location.protocol + '//' + document.domain + ':' + location.port);

        socket.on('connect',function() {
            console.log('test!');
            //socket.send('user connected!!');
            //console.log(socket)
         });

    socket.on('message', function(msg) {
        console.log(msg)});
    return recognizer;
}

var recognizer;
var classLabels;
var socket;

async function init() {
    if (flag == true){
        recognizer = await createModel();
        classLabels = recognizer.wordLabels();
        flag = false;
        //socket.send('user connected!!');
        console.log('init');
    };
    // get class labels
    const labelContainer = document.getElementById("label-container");
    for (let i = 0; i < classLabels.length + 2; i++) {
        labelContainer.appendChild(document.createElement("div"));
    }

    // listen() takes two arguments:
    // 1. A callback function that is invoked anytime a word is recognized.
    // 2. A configuration object with adjustable fields
    recognizer.listen(result => {
        var maxIndex, maxLabel, maxSoundValue = 0;
        const scores = result.scores; // probability of prediction for each class
        // render the probability scores per class




for (let i = 0; i < classLabels.length; i++) {
            const classPrediction = classLabels[i] + ": " + result.scores[i].toFixed(2);
            labelContainer.childNodes[i].innerHTML = classPrediction;
            if(maxSoundValue < result.scores[i].toFixed(2)) {
                maxIndex = i;
                maxSoundValue = result.scores[i].toFixed(2);
              }
            }

        maxLabel = classLabels[maxIndex];
        labelContainer.childNodes[8].innerHTML = "max label name: " + maxLabel;
        labelContainer.childNodes[9].innerHTML = "value: " + maxSoundValue;

        socket.send(maxLabel + " "+ maxSoundValue);





        }, {
        includeSpectrogram: true, // in case listen should return result.spectrogram
        probabilityThreshold: 0.75,
        invokeCallbackOnNoiseAndUnknown: true,
        overlapFactor: 0.75 // probably want between 0.5 and 0.75. More info in README
    });
    // Stop the recognition in 5 seconds.
    //setTimeout(() => recognizer.stopListening(), 5000);

  }
