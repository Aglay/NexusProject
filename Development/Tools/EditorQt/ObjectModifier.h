#pragma once






class ObjectModifier
{
public:
	ObjectModifier( );

	virtual ~ObjectModifier( );

	void Initialize( GameWorld* World );

	EditorObject* GetSelectedObject( );

	// ��ת,����,λ��
	void SetGizmoAdjustMode( eECAdjustMode Mode );	

	eECAdjustMode GetGizmoAdjustMode( );

	// ���ػ�����ռ����
	void SetGizmoAdjustSpace( eECAdjustSpace Space );

	eECAdjustSpace GetGizmoAdjustSpace( );

	void CmdSetSelection( const SelectedActorArray& SelectedActor, bool KeepOld = false , bool Remove = false );

	Vector3 GetGroupSpawnPoint( const Point& MP );

public:	

	virtual void OnMouseMove( const Point& MP );

	virtual void OnMouseLeftButtonDown( const Point& MP );

	virtual void OnMouseLeftButtonUp( const Point& MP );

	void UpdateGizmo( );

public:

	Actor* GetGizmo( ){ return mGizmo;}

private:
	void CreateGizmo( );
	eAdjustAxis PickGizmoAxis( const Ray& PickRay );
	Plane FindGizmoTranslationPlane( const Ray& PickRay, dword TranslationAxis );
	Vector3 GetGizmoIntersect( const Ray& PickRay, const Plane& PlaneToUse, dword TranslationAxis, Vector3& LastPosition );
	
	void BeginAdjustGizmo( const Point& MP );
	void AdjustGizmo( const Point& MP );
	void EndAdjustGizmo( );

	Actor* PickSingleObject( const Ray& PickRay );
	bool VolumeSelect( const Point& Pt1, const Point& Pt2);
	void SingleSelect( const Point& MP );	


private:
	friend class EditorDrawUtilityComponent;

	EditorObject*		mSelectedObject;		// ѡ�е����弯��, ����Ϊ��
	Actor*				mGizmo;					// Gizmo����
	Actor*				mEditorHelper;			// ����ѡ�����弰�����Ĺ���
	eAdjustAxis			mEditorAxis;			// ѡ�е���

	// ʰȡGizmoǰ�������������
	Quaternion			mLastDerivedRotation;
	Vector3				mLastDerivedPosition;
	Vector3				mLastScale;
	Plane				mLastUsedPlane;
	Vector3				mLast3DDelta;
	Vector3				mLastTranslationDelta;
	Vector2				mSavedMousePt;			// Gizmoʰȡ��������λ��
	bool				mIsAdjustingGizmo;		// ���ڵ���Gizmo
	eECAdjustMode		mGizmoAdjustMode;		// Gizmo����ģʽ
	eECAdjustSpace		mGizmoAdjustSpace;		// Gizmo�����ռ䷽ʽ

	bool				mIsVolumeSelecting;		// �Ƿ��������ѡ��
	Point				mVolumeSelectPt1;		// ѡ�е�һ��
	Point				mVolumeSelectPt2;		// ѡ�еڶ���

	GameWorld*			mWorld;

};
