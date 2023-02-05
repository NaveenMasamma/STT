# STT

Speechmatics Client 

Example Communication :-

-> {"message": "StartRecognition", "audio_format": {"type": "file"},
    "transcription_config": {"language": "en", "enable_partials": true}}

 <- {"message": "RecognitionStarted", "id": "807670e9-14af-4fa2-9e8f-5d525c22156e"}

->  "[binary message - AddAudio 1]"
->  "[binary message - AddAudio 2]"

 <- {"message": "AudioAdded", "seq_no": 1}
 <- {"message": "Info", "type": "recognition_quality", "quality": "broadcast", "reason": "Running recognition using a broadcast model quality."}
 <- {"message": "AudioAdded", "seq_no": 2}

->  "[binary message - AddAudio 3]"

 <- {"message": "AudioAdded", "seq_no": 3}

"[asynchronously received transcripts:]"

 <- {"message": "AddPartialTranscript", "metadata": {"start_time": 0.0, "end_time": 0.5399999618530273, "transcript": "One"},
     "results": [{"alternatives": [{"confidence": 0.0, "content": "One"}],
                  "start_time": 0.47999998927116394, "end_time": 0.5399999618530273, "type": "word"}
                ]}
 <- {"message": "AddPartialTranscript", "metadata": {"start_time": 0.0, "end_time": 0.7498992613545260, "transcript": "One to"},
     "results": [{"alternatives": [{"confidence": 0.0, "content": "One"}],
                  "start_time": 0.47999998927116394, "end_time": 0.5399999618530273, "type": "word"},
                 {"alternatives": [{"confidence": 0.0, "content": "to"}],
                  "start_time": 0.6091238623430891, "end_time": 0.7498992613545260, "type": "word"}
                ]}
 <- {"message": "AddPartialTranscript", "metadata": {"start_time": 0.0, "end_time": 0.9488123643240011, "transcript": "One to three"},
     "results": [{"alternatives": [{"confidence": 0.0, "content": "One"}],
                  "start_time": 0.47999998927116394, "end_time": 0.5399999618530273, "type": "word"},
                 {"alternatives": [{"confidence": 0.0, "content": "to"}],
                  "start_time": 0.6091238623430891, "end_time": 0.7498992613545260, "type": "word"}
                 {"alternatives": [{"confidence": 0.0, "content": "three"}],
                  "start_time": 0.8022338627780892, "end_time": 0.9488123643240011, "type": "word"}
                ]}
 <- {"message": "AddTranscript", "metadata": {"start_time": 0.0, "end_time": 0.9488123643240011, "transcript": "One two three."},
     "results": [{"alternatives": [{"confidence": 1.0, "content": "One"}],
                  "start_time": 0.47999998927116394, "end_time": 0.5399999618530273, "type": "word"},
                 {"alternatives": [{"confidence": 1.0, "content": "to"}],
                  "start_time": 0.6091238623430891, "end_time": 0.7498992613545260, "type": "word"}
                 {"alternatives": [{"confidence": 0.96, "content": "three"}],
                  "start_time": 0.8022338627780892, "end_time": 0.9488123643240011, "type": "word"}
                 {"alternatives": [{"confidence": 1.0, "content": "."}],
                  "start_time": 0.9488123643240011, "end_time": 0.9488123643240011, "type": "punctuation", "is_eos": true}
                ]}

"[closing handshake]"

->  {"message":"EndOfStream","last_seq_no":3}

 <- {"message": "EndOfTranscript"}


Google Client 

Example COmmunication :-


results { alternatives { transcript: "tube" } stability: 0.01 }

results { alternatives { transcript: "to be a" } stability: 0.01 }

results { alternatives { transcript: "to be" } stability: 0.9 } results { alternatives { transcript: " or not to be" } stability: 0.01 }

results { alternatives { transcript: "to be or not to be" confidence: 0.92 } alternatives { transcript: "to bee or not to bee" } is_final: true }

results { alternatives { transcript: " that's" } stability: 0.01 }

results { alternatives { transcript: " that is" } stability: 0.9 } results { alternatives { transcript: " the question" } stability: 0.01 }

results { alternatives { transcript: " that is the question" confidence: 0.98 } alternatives { transcript: " that was the question" } is_final: true }
