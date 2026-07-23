-- seed.sql corregido
INSERT INTO public.users(
  user_name,
  user_password,
  user_profile,
  rescue_type,
  first_value,
  confirm_value
)
VALUES(
  encode(digest('public'::BYTEA, 'sha512'), 'hex'),  -- ← hasheado
  'public',
  'PUBLIC',
  'PUBLIC',
  'PUBLIC'::BYTEA,
  'PUBLIC'
)
ON CONFLICT (user_name) DO NOTHING;