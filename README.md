شرح مبسط للنقاط الاساسية في حل واجب المخزن الدائري Circular Buffer :
اول فكرة : تهيئة المخزن 
استخدمت function بسيط مهمتو الاساسية تصفير العداد و مؤشري القراءة و الكتابة 
void init(struct CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

تاني فكرة : الادخال ( الكتابة ) 
استخدمت function ال write بحيث بتضيف حرف جديد بمكان ال tail و قبل ما تضيف بتتاكد اذا المخزن مليان حتى نتجنب ال Overflow 

void write(struct CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\nBuffer Overflow! Cannot add: %c", data);
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE; 
    cb->count++;
}

تالت فكرة : الإزالة ( القراءة )
استخدمت function ال read  يلي بتقوم بقراءة الحرف من عند ال head و قبل ما تقرا رح تتاكد اذا المخزن فاضي لتتجنب ال Underflow

 char read(struct CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\nBuffer Underflow!");
        return '\0'; 
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE;
    cb->count--;
    return data;
}

رابع فكرة : حالات امتلاء المخزن / فراغ المخزن 
عنا ال function هنن isfull و isEmpty بيعتمدو على العداد count و بيقررة بناءا عليه حالة المخزن

bool isFull(struct CircularBuffer *cb) {
    return cb->count == SIZE;
}

bool isEmpty(struct CircularBuffer *cb) {
    return cb->count == 0;
}

الفكرة الاساسية : انو المخزن الدائري بيلف و بيرجع للبداية عند نهاية المصفوفة ، بهي النقطة استخدمت ( % ) 
الكود تجرب بحالتين :
لما يكون ال size = 5 عم تنتج عنا بال output حالة ال Overflow بناءا على الاسم يلي دخلته "rand" و يلي رح يتم دمجه مع العبارة "ce-esy" 

اما لما يكون ال size = 30 فرضاً, رح يتم تنفيذ البرنامج بشكل طبيعي و تظهر كتابة "rand ce-esy"

بالنسبة لحالة ال Underflow فهي بتظهر لما كون عم حاول اقرا من مخزن فارغ تماما من البيانات
