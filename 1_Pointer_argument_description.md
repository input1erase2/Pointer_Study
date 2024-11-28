
# 선요약

- 포인터변수를 인자로 넘길 때, 포인터 매개변수가 생성되며 <mark style="background: #FFF3A3A6;">얕은 복사가 발생</mark>한다.
- 따라서 포인터 매개변수'<u>를 통해</u>' 가해지는 조작은 가리키는 대상에 반영된다. 마치 원본이 한것처럼.
- 하지만, 원본 포인터변수가 갖고있는 값을 바꾸려면 (즉, 주소를 바꾸려면 or 가리키는 대상을 변경하려면) 포인터변수의 주소를 담는 변수, <mark style="background: #FFB8EBA6;">이중포인터를 사용</mark>해야 한다.
- 포인터 매개변수의 값을 변경해도 원본 포인터변수에는 반영이 안 된다.

# 단계

## 1단계: 함수 호출 전

![](https://i.imgur.com/hUArq4F.png)

``` c
// makeNode()
void makeNode(int data) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

// main()
Node* node = makeNode(10);
```

- `Node` 구조체 자료형의 주소를 저장하는 포인터변수 `newNode`를 도식화하면 위와 같습니다.

## 2단계: 실험함수1 호출

![](https://i.imgur.com/41mPiW6.png)

```c
void arguTest1(Node* n1) {
	n1->data = 100;
    n1->next = makeNode(1000);
    n1 = n1->next;
}
```

- 포인터 매개변수 `n1`은 원본 포인터변수`node`를 받습니다.
	- `Node* n1 = node` 라고 생각한다면, shallow copy가 발생합니다.
	- 따라서, `n1`도 '주소 A 구조체'를 가리키는 상태입니다.

![](https://i.imgur.com/h7WteK4.png)

- 화살표 연산자 (참조)로`n1`을 통해 '주소 A 구조체'의 값을 바꾸고 있습니다.
	- 참조 대상이 원본 포인터변수와 동일한 상황입니다. (화살표가 같은 곳을 가리키고 있습니다.)
	- 따라서, <mark style="background: #BBFABBA6;">원본 포인터변수로 참조해서 값을 바꾼것과 똑같이 참조 대상의 값이 변경</mark>됩니다.
- `n1 = n1->next`에서 `n1`이 갖고있는 주소(A)가 `n1->next` (D)로 변경됩니다.
	- 그러나, 이 값은 원본 포인터변수 `node`에는 반영되지 않습니다.
	- 위 그림을 보면, `n1`의 화살표만 '주소 D 구조체'를 가리키도록 바뀌었습니다. `node`는 여전히 '주소 A 구조체'를 가리키고 있습니다.
- 즉, <mark style="background: #FFB8EBA6;">같은 차원의 포인터 매개변수는 원본 포인터처럼 사용(참조대상을 제어) 할 수 있지만, 얕은 복사로 만들어진 복사본이기 때문에 원본 포인터 그 자체에 대한 수정은 불가능함을 확인</mark>할 수 있습니다.

## 3단계. 실험함수 2 호출

![](https://i.imgur.com/vAKL0X9.png)

```c
void arguTest2(Node** n2) {
	(*n2)->data = 200;
    
    if ((*n2)->next != NULL) free((*n2)->next);
    (*n2)->next = makeNode(2000);
    
    node* delNode = (*n2);
    (*n2) = (*n2)->next;
    free(delNode);
}

// main()
arguTest2(&node);
```

- 실험함수1을 빠져나오면서, 포인터 매개변수 `n1`은 생애주기를 마치고 사라집니다.
- `n2`는 2중 포인터 매개변수이므로 실험함수2를 호출할 때 `node`의 주소값을 넘겨주고 있습니다.
	- 실험함수1과의 결정적인 차이점입니다.
	- 실험함수1은 `node`의 복사가 발생했지만, 실험함수2는 `node`의 주소를 넘깁니다.
	- 위 그림대로, `node`를 가리키는 형태의 포인터 매개변수 `n2`가 만들어집니다.
- `node`와 직접적인 연관은 없던 복사본 `n1`을 통해 접근했던 실험함수1과 달리 `n2`는 `node`의 주소를 가지고 있는 포인터변수이므로, `(*n2) = (*n2)->next` 처럼 가리키는 대상을 변경하는게 원본에도 그대로 반영됩니다.
- 즉, <mark style="background: #FFB8EBA6;">포인터변수가 가진 값은 변경하고자 할 때는 한 차원 높은 포인터를 사용해서 주소값을 받아와야</mark> 합니다.
- (이외에도 메모리 낭비를 막기 위해서 해제하는 과정이 중간중간에 껴있지만, 지금 다루는 토픽에 집중하고자 설명은 생략합니다.)

## 결과화면

![](https://i.imgur.com/IltNjoF.png)

- `n1 = n1->next`로 `n1`의 주소가 `0x7FFD_B37A_37F8`에서 `0x5D85_AFF7_76D0`로 변경됩니다.
- 그러나, 이 값은 원본 포인터변수의 주소 `0x5D85_AFF7_72A0`와 다릅니다. 반영이 안된겁니다.
- `(*n2) = (*n2)->next`로 `(*n2)`의 주소가 `0x5D85_AFF7_76D0`로 바뀝니다.
- 위에서 다뤘듯이 `(*n2)`는 `node`와 같습니다. 실제로 원본 포인터변수의 주소가 똑같은 것으로 바뀐것을 확인할 수 있습니다.

